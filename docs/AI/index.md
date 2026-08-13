# AI（人工智能）

> 1.5万字速通LLM主流模型结构（Llama、Qwen、GLM、Deepseek...） - 魔法学院的Chilia的文章 - 知乎
https://zhuanlan.zhihu.com/p/2060741715095560795


---

## 业界主流 LLM

### Claude 系列

主播用不起 Fable，平时最多用用 Opus 和 Sonnet，A 社还是太权威了😭

- 2026.06.09，Claude Fable 5（`claude-fable-5`）
    - [官方新闻](https://www.anthropic.com/claude/fable)：Next generation of intelligence for the hardest knowledge work and coding problems.
- 2026.05.28，Claude Opus 4.8（`claude-opus-4.8`）
    - [官方新闻](https://www.anthropic.com/claude/opus)：Hybrid reasoning model built for serious coding and AI agents, featuring a 1M context window
    - LOG：2026.04.16，Opus 4.7；2026.02.05，Opus 4.6；2025.11.24，Opus 4.5
- 2026.06.30，Claude Sonnet 5（`claude-sonnet-5`）
    - [官方新闻](https://www.anthropic.com/claude/sonnet)：Hybrid reasoning model with fast, capable intelligence for real-time agents and high-volume work, featuring a 1M context window
    - LOG：2026.02.17，Sonnet 4.6；2025.09.29，Sonnet 4.5；2025.05.22，Sonnet 4

### GPT 系列

- 2026.07.09，GPT-5.6（`gpt-5.6-{sol,terra,luna}`）
    - 全新旗舰模型 `Sol` > 适用于日常工作的均衡模型 `Terra` > 极具性价比的模型 `Luna`
    - GPT-5.5 已经相当牛逼，我的课程大作业全靠的它
    - [GPT-5.6 官方新闻](https://openai.com/zh-Hans-CN/index/gpt-5-6/)：GPT‑5.6：随宏大目标灵活扩展的前沿智能
    - [GPT-5.5 官方新闻](https://openai.com/zh-Hans-CN/index/introducing-gpt-5-5/)：重磅发布 GPT‑5.5
    - [GPT-5.4 官方新闻](https://openai.com/zh-Hans-CN/index/introducing-gpt-5-4/)：GPT‑5.4 震撼登场
    - LOG：2026.04.23，GPT-5.5；2026.03.05，GPT-5.4
- GPT-1 ~ GPT-4
    - [2018.06，GPT-1 论文](https://cdn.openai.com/research-covers/language-unsupervised/language_understanding_paper.pdf)：Improving Language Understanding by Generative Pre-Training
    - [2019.02，GPT-2 论文](https://cdn.openai.com/better-language-models/language_models_are_unsupervised_multitask_learners.pdf)：Language Models are Unsupervised Multitask Learners
    - [2020.05，GPT-3 论文](https://arxiv.org/pdf/2005.14165)：Language Models are Few-Shot Learners
    - [2023.03，GPT-4 论文](https://arxiv.org/pdf/2303.08774)：GPT-4 Technical Report
    - 合集解读推荐[这篇](https://zhuanlan.zhihu.com/p/18104675680)

### Gemini 系列

最近出的 Gemini 3.6 Flash 蠢如豆包，暂不考虑使用。等牛一点了再用。

### DeepSeek 系列

DeepSeek 系列模型均**开源模型权重**，具体可见 https://huggingface.co/collections/deepseek-ai/deepseek-v4。

- 2026.08.13，DeepSeek-V4（`deepseek-v4-{pro,flash}`）
    - DS 的价格亲民实惠，但确实有点蠢（（
    - [官方新闻](https://api-docs.deepseek.com/zh-cn/news/news260813/)：DeepSeek-V4-Pro 正式版上线
    - [官方新闻](https://api-docs.deepseek.com/zh-cn/news/news260424)：DeepSeek-V4 预览版：迈入百万上下文普惠时代
    - [论文](https://arxiv.org/pdf/2606.19348)：Towards Highly Efficient Million-Token Context Intelligence
- 2025.01，DeepSeek-R1（`deepseek-reasoner`），已淘汰
    - 在后训练阶段大规模使用 RL，在仅有极少标注数据的情况下，极大提升了模型推理能力
    - [官方新闻](https://api-docs.deepseek.com/zh-cn/news/news250120)：DeepSeek-R1 发布，性能对标 OpenAI o1 正式版
    - [论文](https://arxiv.org/pdf/2501.12948)：DeepSeek-R1: Incentivizing Reasoning Capability in LLMs via Reinforcement Learning
- 2024.12，DeepSeek-V3（`deepseek-chat`），已淘汰
    - 自研 MoE 模型，671B 参数，激活 37B，在 14.8T token 上进行了预训练
    - [官方新闻](https://api-docs.deepseek.com/zh-cn/news/news1226)：DeepSeek-V3 正式发布
    - [论文](https://arxiv.org/pdf/2412.19437)：DeepSeek-V3 Technical Report

### GLM 系列

- 2026.06，GLM-5.2（`glm-5.2`）
    - GLM-5.2 整体表现介于 Claude Opus 4.7 与 4.8 之间，还是相当牛的
    - [官方新闻](https://z.ai/blog/glm-5.2)：GLM-5.2: Built for Long-Horizon Tasks
    - [GLM-5 系列论文](https://arxiv.org/pdf/2602.15763)：GLM-5: from Vibe Coding to Agentic Engineering

### Qwen 系列

咕，平时不用。