# Pinpoint
Pinpoint - text messenger made with Qt5. First release I did for my university coursework.<br/>
All communication between the client and server proceeds using JSON packets.
## How does it look like?
<h3> Client app </h3>

<table>
  <tr>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase-client-app-windows.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase-client-app-1.png"></td>
  </tr>
</table>
<h3> Server app </h3>
<p align="center">
<img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase-server-app.png">
</p>

<h2> How does it work? </h2>
<p>It uses TCP/IP protocol to exchange JSON packets.<br/>
  The server is only router of packets, so all messages are stored on client's memory.
</p>

<h2> Tests </h2>
<p>I tested it on a local network on several computers.<br/>
  Moreover I faced some issues on older machines with Windows 7/Windows 8.1 or rather with displaying emoticons.
</p>
<table>
  <tr>
    <th>Windows 11</th>
    <th>Windows 10</th>
    <th>Windows 8.1</th>
    <th>Windows 7</th>
    <th>Windows 7 (with font)</th>
  </tr>
  <tr>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/win11_emj.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/win10.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/win8_emj.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/win7_emj.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/win7-with-font_emj.png"></td>
  </tr>
</table>
