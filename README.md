# Alan 的个人博客

这是我的个人博客项目，使用 MkDocs 和 Material 主题构建。

## 本地开发

### 安装依赖

```bash
pip install -r requirements.txt
```

### 本地预览

```bash
mkdocs serve
```

然后在浏览器中访问 http://127.0.0.1:8000

### 构建站点

```bash
mkdocs build
```

## 部署

推送到 `main` 分支后，GitHub Actions 会自动构建并部署到 GitHub Pages。

访问地址：https://phoenix-alan233.github.io

## 添加新文章

1. 在 `docs/` 目录下创建新的 Markdown 文件
2. 在 `mkdocs.yml` 的 `nav` 部分添加导航链接
3. 提交并推送到 GitHub

## 技术栈

- [MkDocs](https://www.mkdocs.org/)
- [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/)
- GitHub Pages
- GitHub Actions
