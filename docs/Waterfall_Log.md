# F12 Network Timing Analysis (Waterfall)

Use this document to record the network timing data captured from the browser developer tools (F12).

## Request Timing Breakdown

| Phase | Time (ms) | Description |
|-------|-----------|-------------|
| DNS Lookup | | Time to resolve the ESP32's hostname |
| Initial Connection (TCP) | | Time for the 3-way handshake |
| SSL/TLS Handshake | | (N/A for HTTP) |
| Request Sent | | Time to send the request packet |
| Waiting (TTFB) | | Time for the server to process and send the first byte |
| Content Download | | Time to download the entire response |

## Diagnostic Observations

- **Bottleneck Identification:** Which phase takes the most time? Why?
- **Server Performance:** What does the TTFB tell you about the ESP32's processing speed?
- **Network Overhead:** How much time is spent just establishing the connection?
