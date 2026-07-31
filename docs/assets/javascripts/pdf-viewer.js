// 优化的 PDF 查看器
document.addEventListener('DOMContentLoaded', function() {
  const pdfContainers = document.querySelectorAll('.pdf-container');

  pdfContainers.forEach(container => {
    const object = container.querySelector('object');
    if (object) {
      const pdfUrl = object.getAttribute('data');

      // 使用 #toolbar=0 参数隐藏工具栏（适用于某些浏览器）
      if (pdfUrl && !pdfUrl.includes('#')) {
        object.setAttribute('data', pdfUrl + '#toolbar=0&navpanes=0&scrollbar=1');
      }

      // 添加自定义控制栏
      const controls = document.createElement('div');
      controls.className = 'pdf-controls';
      controls.innerHTML = `
        <a href="${pdfUrl}" download class="pdf-control-btn" title="下载 PDF">
          <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="20" height="20">
            <path fill="currentColor" d="M5,20H19V18H5M19,9H15V3H9V9H5L12,16L19,9Z" />
          </svg>
        </a>
        <a href="${pdfUrl}" target="_blank" class="pdf-control-btn" title="在新标签页打开">
          <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="20" height="20">
            <path fill="currentColor" d="M14,3V5H17.59L7.76,14.83L9.17,16.24L19,6.41V10H21V3M19,19H5V5H12V3H5C3.89,3 3,3.9 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V12H19V19Z" />
          </svg>
        </a>
      `;

      container.appendChild(controls);
    }
  });
});
