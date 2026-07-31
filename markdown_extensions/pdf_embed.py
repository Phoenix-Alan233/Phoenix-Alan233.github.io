"""
自定义 Markdown 扩展：PDF 嵌入支持

使用方法：
!pdf[路径/到/文件.pdf]
或
!pdf[路径/到/文件.pdf]{height=600px}
"""

from markdown.extensions import Extension
from markdown.inlinepatterns import InlineProcessor
from markdown.blockprocessors import BlockProcessor
import xml.etree.ElementTree as etree
import re


class PDFInlineProcessor(InlineProcessor):
    """内联 PDF 处理器"""

    def handleMatch(self, m, data):
        pdf_path = m.group(1)
        options = m.group(2) if m.group(2) else ""

        # 解析选项
        height = "80vh"
        if options:
            height_match = re.search(r'height=([^\s}]+)', options)
            if height_match:
                height = height_match.group(1)

        # 创建 PDF 容器
        container = etree.Element('div')
        container.set('class', 'pdf-container')
        container.set('style', f'height: {height}')

        # 创建 object 标签
        obj = etree.SubElement(container, 'object')
        obj.set('data', pdf_path + '#toolbar=0&navpanes=0&scrollbar=1')
        obj.set('type', 'application/pdf')

        # 创建 fallback
        fallback = etree.SubElement(obj, 'div')
        fallback.set('class', 'pdf-fallback')

        p = etree.SubElement(fallback, 'p')
        p.text = '您的浏览器不支持 PDF 预览'

        download_div = etree.SubElement(fallback, 'div')
        download_div.set('class', 'pdf-download')

        link = etree.SubElement(download_div, 'a')
        link.set('href', pdf_path)
        link.set('download', '')
        link.set('class', 'download-btn')
        link.text = '下载 PDF'

        return container, m.start(0), m.end(0)


class PDFBlockProcessor(BlockProcessor):
    """块级 PDF 处理器"""

    RE = re.compile(r'^\!pdf\[([^\]]+)\](?:\{([^\}]*)\})?$')

    def test(self, parent, block):
        return bool(self.RE.search(block))

    def run(self, parent, blocks):
        block = blocks.pop(0)
        m = self.RE.search(block)

        if m:
            pdf_path = m.group(1)
            options = m.group(2) if m.group(2) else ""

            # 解析选项
            height = "80vh"
            if options:
                height_match = re.search(r'height=([^\s}]+)', options)
                if height_match:
                    height = height_match.group(1)

            # 创建 PDF 容器
            container = etree.SubElement(parent, 'div')
            container.set('class', 'pdf-container')
            container.set('style', f'height: {height}')

            # 创建 object 标签
            obj = etree.SubElement(container, 'object')
            obj.set('data', pdf_path + '#toolbar=0&navpanes=0&scrollbar=1')
            obj.set('type', 'application/pdf')

            # 创建 fallback
            fallback = etree.SubElement(obj, 'div')
            fallback.set('class', 'pdf-fallback')

            p = etree.SubElement(fallback, 'p')
            p.text = '您的浏览器不支持 PDF 预览'

            download_div = etree.SubElement(fallback, 'div')
            download_div.set('class', 'pdf-download')

            link = etree.SubElement(download_div, 'a')
            link.set('href', pdf_path)
            link.set('download', '')
            link.set('class', 'download-btn')
            link.text = '下载 PDF'


class PDFExtension(Extension):
    """PDF 扩展"""

    def extendMarkdown(self, md):
        # 添加块级处理器
        md.parser.blockprocessors.register(
            PDFBlockProcessor(md.parser), 'pdf_block', 175
        )


def makeExtension(**kwargs):
    return PDFExtension(**kwargs)
