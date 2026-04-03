Viewed basic-07-unit-http-lifecycle.html:1-393

針對 **`basic-07-unit-http-lifecycle` (HTTP 協議與請求生命週期)** 單元，這是學員從「功能開發者」轉型為「效能工程師」的核心課程。它要求學員具備 **通訊診斷 (Network Diagnostics)** 與 **延遲優化 (Latency Optimization)** 的思維，學習如何利用瀏覽器開發者工具 (F12) 將隱形的網路握手視覺化，並掌握「連線複用 (Keep-Alive)」這類工業級技術如何顯著提升物聯網設備的反應速度。

以下是在 **GitHub Classroom** 部署其作業 (Assignments) 的具體建議：

### 1. 範本倉庫 (Template Repo) 配置建議
通訊生命週期作業的核心在於「量化分析」與「標準實作」，範本應包含診斷工具說明與性能對比範本，建議包含：
*   **📂 `src/main.cpp`**：**RESTful API 實作區**。學員需在此實作 `/api/status` (GET) 與 `/api/command` (POST) 路由，並學習如何手動控制 `Connection` 標頭以測試效能差異。
*   **📂 `README.md`**：**網路時序診斷報告**。提供「Waterfall (瀑布圖) 分析表」範本，要求學員填入：DNS 查詢、TCP 建立與 TTFB (首字節時間) 的具體毫秒數。
*   **📂 `docs/PERFORMANCE_DUEL.md`**：**效能競賽紀錄**。預設一個表格，讓學員記錄在「Connection: Close」與「Connection: Keep-Alive」兩種模式下，連續發送 50 次指令的總耗時對比。
*   **📂 `assets/timing_screenshot.png`**：要求學員附上 F12 Network 面板中的時序分佈截圖。

---

### 2. 作業任務部署細節

#### 任務 1：「封包捕手」F12 請求時序解析 (Network Diagnostic Lab)
*   **目標**：透過瀏覽器開發者工具將抽象的網路階層具象化，識別出「連線階段」與「資料傳輸階段」的性能界線。
*   **Classroom 部署建議**：
    *   **時序解剖**：存取 ESP32 網頁並擷取時序圖。
    *   **瓶頸診斷**：**核心關鍵點**。學員必須識別出 TTFB 代表的是「ESP32 的處理時間」，而 TCP Connect 代表的是「連線握手開銷」。
    *   **驗證要點**：README 中是否準確標註了各階段的毫秒數並提出了延遲的主因假設？

#### 任務 2：「自建路由」RESTful API 實作 (API Architect Lab)
*   **目標**：建立符合現代 Web 開發規範的通訊接口，掌握 JSON 標頭配置與狀態碼語義。
*   **Classroom 部署建議**：
    *   **規範實施**：實作 `/api/status` 回傳 JSON（如 `{ "free_heap": 12345 }`）。
    *   **命令接收**：實作 `POST /api/command` 解析 Body 指令。
    *   **標準化回應**：成功時回傳 `200 OK`，若指令格式不對則回傳 `400 Bad Request`。
    *   **驗證要點**：藉由 Postman 或網頁測試，確認標頭中 `Content-Type` 是否正確宣告為 `application/json`。

#### 任務 3：「連線優化師」Keep-Alive 效能對比 (Performance Lab)
*   **目標**：親手驗證 TCP 三向握手的成本，學習在「高頻通訊」場景下如何透過保持連線來節省超過 50% 的延遲。
*   **Classroom 部署建議**：
    *   **壓力測試**：執行 50 次高頻控制封包。
    *   **數據量化**：對比「一發一斷」與「長連線」的總時間差。
    *   **原理深挖**：**核心思想考題**。請學員在報告中說明：為什麼長連線在第二次以後的請求中，不再出現 TCP Connect 的耗時？
    *   **最終 Commit**：封裝具備效能優化意識的通訊代碼並 Push。

---

### 3. 通訊診斷與效能優化點評標準 (Diagnostics & Latency Standards)
此單元的價值在於 **「對通訊細節的洞察力與對網路協定成本的量化控制能力」**：
*   [ ] **時序解析正確性**：是否能正確區分連線建立時間 (TCP) 與伺服器反應時間 (TTFB)？
*   [ ] **RESTful 專業度**：路由設計是否簡潔？狀態碼的選用是否符合開發慣例？
*   [ ] **優化結論驅動**：是否能從數據中得出「Keep-Alive 對即時控制（如遙控車）至關重要」的工程結論？

### 📁 推薦範本結構 (GitHub Classroom Template)：
```text
.
├── src/main.cpp         # 核心：API 路由實作與 Connection 標頭控制
├── docs/Waterfall_Log.md # 文檔：F12 時序分析數據與瓶頸解說
├── docs/Performance.csv # 數據：Keep-Alive 開啟前後的耗時對比表
├── README.md            # 總結：我如何透過網路診斷找出通訊瓶頸並完成效能優化
└── assets/DevTools.png  # 證據：F12 Network 面板的時序截圖證據
```

透過這種部署方式，學生能體驗到 **「好的全端工程師，不是能傳送數據的人，而是能透視封包旅程、找出那消失的 200ms 延遲、並用最合適的連線策略讓設備反應『如絲般順滑』的通訊診斷專家」**。掌握 HTTP 生命週期與效能優化技術後，學員將擁有了開發「高反應遙控系統、高併發數據採集器、流暢網頁控制台」最專業也最核心的系統開發實力！_
|
|
太精采了！我們已經將 **基礎 07**（通訊架構與生命週期）的所有 Classroom 部署建議總結完成了。這標誌著學員終於能「看見」網路的運行，並從最底層優化系統體驗。恭喜！基礎課程的通訊實力已經正式封頂！
