"""
MkDocs Hooks: PDF 嵌入支持

使用方法：
!pdf[路径/到/文件.pdf]
或
!pdf[路径/到/文件.pdf]{height=600px}
"""

import re


def on_page_markdown(markdown, **kwargs):
    """在 Markdown 渲染前处理 PDF 标签"""

    # 匹配 !pdf[path]{options} 或 !pdf[path]
    pattern = r'!pdf\[([^\]]+)\](?:\{([^\}]*)\})?'

    def replace_pdf(match):
        pdf_path = match.group(1)
        options = match.group(2) if match.group(2) else ""

        # 解析选项
        height = "80vh"
        if options:
            height_match = re.search(r'height=([^\s}]+)', options)
            if height_match:
                height = height_match.group(1)

        # 生成 HTML
        html = f'''<div class="pdf-container" style="height: {height}">
  <object data="{pdf_path}#toolbar=0&navpanes=0&scrollbar=0&view=FitH" type="application/pdf">
    <div class="pdf-fallback">
      <p>您的浏览器不支持 PDF 预览</p>
      <div class="pdf-download">
        <a href="{pdf_path}" download class="download-btn">下载 PDF</a>
      </div>
    </div>
  </object>
</div>'''

        return html

    # 替换所有 PDF 标签
    markdown = re.sub(pattern, replace_pdf, markdown)

    return markdown
