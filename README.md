<h1> Pinpoint </h1>
<img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/icon-b.png" width="20%">
<p>
Pinpoint - text messenger made with Qt 5. First release I did for my university coursework.<br/>
</p>
<h2> How does it look like? </h2>
<h3> Client app </h3>

<table>
  <tr>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/showcase-client-app-windows.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/showcase-client-app-1.png"></td>
  </tr>
</table>
<h3> Server app </h3>
<p align="center">
<img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/showcase-server-app.png">
</p>

<h2> How does it work? </h2>
<p>
  It uses TCP/IP protocol to exchange JSON packets.
  The server is only router of packets, so all messages are stored on client's memory.
</p>
<p>Start server and open client, enter your nickname</p>
<p><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/profile.png"></p>
<p>Click on the "Server" to establish the connection with the server. (Default port is 1967)</p>
<p><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/connect-to-server.png"></p>
<p>In addition you can review participants and their joining time.</p>
<p><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/members.png"></p>
<p>Also I can't help remembering window with emoticons, I like it best!</p>
<p><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/win11_emj.png"></p>
<p>To get an array of emoticons I wrote a python script and parsed all emojies from https://unicode.org/emoji/charts/full-emoji-list.html. Not all of them were adequately displayed, so I selected some of them.</p>
<pre><code>
const char32_t emojies[] = {U'😀', U'😃', U'😄', U'😁', U'😆', U'😅', U'🤣', U'😂', U'🙂', U'🙃', U'😉', U'😊', U'😇', U'🥰', U'😍', U'🤩', U'😘', U'😗', U'😚', U'😙', U'😋', U'😛', U'😜', U'🤪', U'😝', U'🤑', U'🤗', U'🤭', U'🤫', U'🤔', U'🤐', U'🤨', U'😐', U'😑', U'😶', U'😏', U'😒', U'🙄', U'😬', U'🤥', U'😌', U'😔', U'😪', U'🤤', U'😴', U'😷', U'🤒', U'🤕', U'🤢', U'🤮', U'🤧', U'🥵', U'🥶', U'🥴', U'😵', U'🤯', U'🤠', U'🥳', U'😎', U'🤓', U'🧐', U'😕', U'😟', U'🙁', U'☹', U'😮', U'😯', U'😲', U'😳', U'🥺', U'😦', U'😧', U'😨', U'😰', U'😥', U'😢', U'😭', U'😱', U'😖', U'😣', U'😞', U'😓', U'😩', U'😫', U'🥱', U'😤', U'😡', U'😠', U'🤬', U'😈', U'👿', U'💀', U'☠', U'💩', U'🤡', U'👹', U'👺', U'👻', U'👽', U'👾', U'🤖', U'😺', U'😸', U'😹', U'😻', U'😼', U'😽', U'🙀', U'😿', U'😾', U'🙈', U'🙉', U'🙊', U'💋', U'💌', U'💘', U'💝', U'💖', U'💗', U'💓', U'💞', U'💕', U'💟', U'❣', U'💔', U'❤', U'🧡', U'💛', U'💚', U'💙', U'💜', U'🤎', U'🖤', U'🤍', U'💯', U'💢', U'💥', U'💫', U'💦', U'💨', U'🕳', U'💣', U'💬', U'🗨', U'🗯', U'💭', U'💤', U'👋', U'🤚', U'🖐', U'✋', U'🖖', U'👌', U'🤏', U'✌', U'🤞', U'🤟', U'🤘', U'🤙', U'👈', U'👉', U'👆', U'🖕', U'👇', U'☝', U'👍', U'👎', U'✊', U'👊', U'🤛', U'🤜', U'👏', U'🙌', U'👐', U'🤲', U'🤝', U'🙏', U'✍', U'💅', U'🤳', U'💪', U'🦾', U'🦿', U'🦵', U'🦶', U'👂', U'🦻', U'👃', U'🧠', U'🦷', U'🦴', U'👀', U'👁', U'👅', U'👄', U'👶', U'🧒', U'👦', U'👧', U'🧑', U'👱', U'👨', U'🧔', U'👩', U'🧓', U'👴', U'👵', U'🙍', U'🙎', U'🙅', U'🙆', U'💁', U'🙋', U'🧏', U'🙇', U'🤦', U'🤷', U'👮', U'🕵', U'💂', U'👷', U'🤴', U'👸', U'👳', U'👲', U'🧕', U'🤵', U'👰', U'🤰', U'🤱', U'👼', U'🎅', U'🤶', U'🦸', U'🦹', U'🧙', U'🧚', U'🧛', U'🧜', U'🧝', U'🧞', U'🧟', U'💆', U'💇', U'🚶', U'🧍', U'🧎', U'🏃', U'💃', U'🕺', U'🕴', U'👯', U'🧖', U'🧗', U'🤺', U'🏇', U'⛷', U'🏂', U'🏌', U'🏄', U'🚣', U'🏊', U'⛹', U'🏋', U'🚴', U'🚵', U'🤸', U'🤼', U'🤽', U'🤾', U'🤹', U'🧘', U'🛀', U'🛌', U'👭', U'👫', U'👬', U'💏', U'💑', U'👪', U'🗣', U'👤', U'👥', U'👣', U'🦰', U'🦱', U'🦳', U'🦲', U'🐵', U'🐒', U'🦍', U'🦧', U'🐶', U'🐕', U'🦮', U'🐩', U'🐺', U'🦊', U'🦝', U'🐱', U'🐈', U'🦁', U'🐯', U'🐅', U'🐆', U'🐴', U'🐎', U'🦄', U'🦓', U'🦌', U'🐮', U'🐂', U'🐃', U'🐄', U'🐷', U'🐖', U'🐗', U'🐽', U'🐏', U'🐑', U'🐐', U'🐪', U'🐫', U'🦙', U'🦒', U'🐘', U'🦏', U'🦛', U'🐭', U'🐁', U'🐀', U'🐹', U'🐰', U'🐇', U'🐿', U'🦔', U'🦇', U'🐻', U'🐨', U'🐼', U'🦥', U'🦦', U'🦨', U'🦘', U'🦡', U'🐾', U'🦃', U'🐔', U'🐓', U'🐣', U'🐤', U'🐥', U'🐦', U'🐧', U'🕊', U'🦅', U'🦆', U'🦢', U'🦉', U'🦩', U'🦚', U'🦜', U'🐸', U'🐊', U'🐢', U'🦎', U'🐍', U'🐲', U'🐉', U'🦕', U'🦖', U'🐳', U'🐋', U'🐬', U'🐟', U'🐠', U'🐡', U'🦈', U'🐙', U'🐚', U'🐌', U'🦋', U'🐛', U'🐜', U'🐝', U'🐞', U'🦗', U'🕷', U'🕸', U'🦂', U'🦟', U'🦠', U'💐', U'🌸', U'💮', U'🏵', U'🌹', U'🥀', U'🌺', U'🌻', U'🌼', U'🌷', U'🌱', U'🌲', U'🌳', U'🌴', U'🌵', U'🌾', U'🌿', U'☘', U'🍀', U'🍁', U'🍂', U'🍃', U'🍇', U'🍈', U'🍉', U'🍊', U'🍋', U'🍌', U'🍍', U'🥭', U'🍎', U'🍏', U'🍐', U'🍑', U'🍒', U'🍓', U'🥝', U'🍅',  U'🥥', U'🥑', U'🍆', U'🥔', U'🥕', U'🌽', U'🌶', U'🥒', U'🥬', U'🥦', U'🧄', U'🧅', U'🍄', U'🥜', U'🌰', U'🍞', U'🥐', U'🥖', U'🥨', U'🥯', U'🥞', U'🧇', U'🧀', U'🍖', U'🍗', U'🥩', U'🥓', U'🍔', U'🍟', U'🍕', U'🌭', U'🥪', U'🌮', U'🌯', U'🥙', U'🧆', U'🥚', U'🍳', U'🥘', U'🍲', U'🥣', U'🥗', U'🍿', U'🧈', U'🧂', U'🥫', U'🍱', U'🍘', U'🍙', U'🍚', U'🍛', U'🍜', U'🍝', U'🍠', U'🍢', U'🍣', U'🍤', U'🍥', U'🥮', U'🍡', U'🥟', U'🥠', U'🥡', U'🦀', U'🦞', U'🦐', U'🦑', U'🦪', U'🍦', U'🍧', U'🍨', U'🍩', U'🍪', U'🎂', U'🍰', U'🧁', U'🥧', U'🍫', U'🍬', U'🍭', U'🍮', U'🍯', U'🍼', U'🥛', U'☕', U'🍵', U'🍶', U'🍾', U'🍷', U'🍸', U'🍹', U'🍺', U'🍻', U'🥂', U'🥃', U'🥤', U'🧃', U'🧉', U'🧊', U'🥢', U'🍽', U'🍴', U'🥄', U'🔪', U'🏺', U'🌍', U'🌎', U'🌏', U'🌐', U'🗺', U'🗾', U'🧭', U'🏔', U'⛰', U'🌋', U'🗻', U'🏕', U'🏖', U'🏜', U'🏝', U'🏞', U'🏟', U'🏛', U'🏗', U'🧱', U'🏘', U'🏚', U'🏠', U'🏡', U'🏢', U'🏣', U'🏤', U'🏥', U'🏦', U'🏨', U'🏩', U'🏪', U'🏫', U'🏬', U'🏭', U'🏯', U'🏰', U'💒', U'🗼', U'🗽', U'⛪', U'🕌', U'🛕', U'🕍', U'⛩', U'🕋', U'⛲', U'⛺', U'🌁', U'🌃', U'🏙', U'🌄', U'🌅', U'🌆', U'🌇', U'🌉', U'♨', U'🎠', U'🎡', U'🎢', U'💈', U'🎪', U'🚂', U'🚃', U'🚄', U'🚅', U'🚆', U'🚇', U'🚈', U'🚉', U'🚊', U'🚝', U'🚞', U'🚋', U'🚌', U'🚍', U'🚎', U'🚐', U'🚑', U'🚒', U'🚓', U'🚔', U'🚕', U'🚖', U'🚗', U'🚘', U'🚙', U'🚚', U'🚛', U'🚜', U'🏎', U'🏍', U'🛵', U'🦽', U'🦼', U'🛺', U'🚲', U'🛴', U'🛹', U'🚏', U'🛣', U'🛤', U'🛢', U'⛽', U'🚨', U'🚥', U'🚦', U'🛑', U'🚧', U'⚓', U'⛵', U'🛶', U'🚤', U'🛳', U'⛴', U'🛥', U'🚢', U'✈', U'🛩', U'🛫', U'🛬', U'🪂', U'💺', U'🚁', U'🚟', U'🚠', U'🚡', U'🛰', U'🚀', U'🛸', U'🛎', U'🧳', U'⌛', U'⏳', U'⌚', U'⏰', U'⏱', U'⏲', U'🕰', U'🕛', U'🕧', U'🕐', U'🕜', U'🕑', U'🕝', U'🕒', U'🕞', U'🕓', U'🕟', U'🕔', U'🕠', U'🕕', U'🕡', U'🕖', U'🕢', U'🕗', U'🕣', U'🕘', U'🕤', U'🕙', U'🕥', U'🕚', U'🕦', U'🌑', U'🌒', U'🌓', U'🌔', U'🌕', U'🌖', U'🌗', U'🌘', U'🌙', U'🌚', U'🌛', U'🌜', U'🌡', U'☀', U'🌝', U'🌞', U'🪐', U'⭐', U'🌟', U'🌠', U'🌌', U'☁', U'⛅', U'⛈', U'🌤', U'🌥', U'🌦', U'🌧', U'🌨', U'🌩', U'🌪', U'🌫', U'🌬', U'🌀', U'🌈', U'🌂', U'☂', U'☔', U'⛱', U'⚡', U'❄', U'☃', U'⛄', U'☄', U'🔥', U'💧', U'🌊', U'🎃', U'🎄', U'🎆', U'🎇', U'🧨', U'✨', U'🎈', U'🎉', U'🎊', U'🎋', U'🎍', U'🎎', U'🎏', U'🎐', U'🎑', U'🧧', U'🎀', U'🎁', U'🎗', U'🎟', U'🎫', U'🎖', U'🏆', U'🏅', U'🥇', U'🥈', U'🥉', U'⚽', U'⚾', U'🥎', U'🏀', U'🏐', U'🏈', U'🏉', U'🎾', U'🥏', U'🎳', U'🏏', U'🏑', U'🏒', U'🥍', U'🏓', U'🏸', U'🥊', U'🥋', U'🥅', U'⛳', U'⛸', U'🎣', U'🤿', U'🎽', U'🎿', U'🛷', U'🥌', U'🎯', U'🪀', U'🪁', U'🎱', U'🔮', U'🧿', U'🎮', U'🕹', U'🎰', U'🎲', U'🧩', U'🧸', U'♠', U'♥', U'♦', U'♣', U'♟', U'🃏', U'🀄', U'🎴', U'🎭', U'🖼', U'🎨', U'🧵', U'🧶', U'👓', U'🕶', U'🥽', U'🥼', U'🦺', U'👔', U'👕', U'👖', U'🧣', U'🧤', U'🧥', U'🧦', U'👗', U'👘', U'🥻', U'🩱', U'🩲', U'🩳', U'👙', U'👚', U'👛', U'👜', U'👝', U'🛍', U'🎒', U'👞', U'👟', U'🥾', U'🥿', U'👠', U'👡', U'🩰', U'👢', U'👑', U'👒', U'🎩', U'🎓', U'🧢', U'⛑', U'📿', U'💄', U'💍', U'💎', U'🔇', U'🔈', U'🔉', U'🔊', U'📢', U'📣', U'📯', U'🔔', U'🔕', U'🎼', U'🎵', U'🎶', U'🎙', U'🎚', U'🎛', U'🎤', U'🎧', U'📻', U'🎷', U'🎸', U'🎹', U'🎺', U'🎻', U'🪕', U'🥁', U'📱', U'📲', U'☎', U'📞', U'📟', U'📠', U'🔋', U'🔌', U'💻', U'🖥', U'🖨', U'⌨', U'🖱', U'🖲', U'💽', U'💾', U'💿', U'📀', U'🧮', U'🎥', U'🎞', U'📽', U'🎬', U'📺', U'📷', U'📸', U'📹', U'📼', U'🔍', U'🔎', U'🕯', U'💡', U'🔦', U'🏮', U'🪔', U'📔', U'📕', U'📖', U'📗', U'📘', U'📙', U'📚', U'📓', U'📒', U'📃', U'📜', U'📄', U'📰', U'🗞', U'📑', U'🔖', U'🏷', U'💰', U'💴', U'💵', U'💶', U'💷', U'💸', U'💳', U'🧾', U'💹', U'✉', U'📧', U'📨', U'📩', U'📤', U'📥', U'📦', U'📫', U'📪', U'📬', U'📭', U'📮', U'🗳', U'✏', U'✒', U'🖋', U'🖊', U'🖌', U'🖍', U'📝', U'💼', U'📁', U'📂', U'🗂', U'📅', U'📆', U'🗒', U'🗓', U'📇', U'📈', U'📉', U'📊', U'📋', U'📌', U'📍', U'📎', U'🖇', U'📏', U'📐', U'✂', U'🗃', U'🗄', U'🗑', U'🔒', U'🔓', U'🔏', U'🔐', U'🔑', U'🗝', U'🔨', U'🪓', U'⛏', U'⚒', U'🛠', U'🗡', U'⚔', U'🔫', U'🏹', U'🛡', U'🔧', U'🔩', U'⚙', U'🗜', U'⚖', U'🦯', U'🔗', U'⛓', U'🧰', U'🧲', U'⚗', U'🧪', U'🧫', U'🧬', U'🔬', U'🔭', U'📡', U'💉', U'🩸', U'💊', U'🩹', U'🩺', U'🚪', U'🛏', U'🛋', U'🪑', U'🚽', U'🚿', U'🛁', U'🪒', U'🧴', U'🧷', U'🧹', U'🧺', U'🧻', U'🧼', U'🧽', U'🧯', U'🛒', U'🚬', U'⚰', U'⚱', U'🗿', U'🏧', U'🚮', U'🚰', U'♿', U'🚹', U'🚺', U'🚻', U'🚼', U'🚾', U'🛂', U'🛃', U'🛄', U'🛅', U'⚠', U'🚸', U'⛔', U'🚫', U'🚳', U'🚭', U'🚯', U'🚱', U'🚷', U'📵', U'🔞', U'☢', U'☣', U'⬆', U'↗', U'➡', U'↘', U'⬇', U'↙', U'⬅', U'↖', U'↕', U'↔', U'↩', U'↪', U'⤴', U'⤵', U'🔃', U'🔄', U'🔙', U'🔚', U'🔛', U'🔜', U'🔝', U'🛐', U'⚛', U'🕉', U'✡', U'☸', U'☯', U'✝', U'☦', U'☪', U'☮', U'🕎', U'🔯', U'♈', U'♉', U'♊', U'♋', U'♌', U'♍', U'♎', U'♏', U'♐', U'♑', U'♒', U'♓', U'⛎', U'🔀', U'🔁', U'🔂', U'▶', U'⏩', U'⏭', U'⏯', U'◀', U'⏪', U'⏮', U'🔼', U'⏫', U'🔽', U'⏬', U'⏸', U'⏹', U'⏺', U'⏏', U'🎦', U'🔅', U'🔆', U'📶', U'📳', U'📴', U'♀', U'♂', U'⚧', U'✖', U'➕', U'➖', U'➗', U'♾', U'‼', U'⁉', U'❓', U'❔', U'❕', U'❗', U'〰', U'💱', U'💲', U'⚕', U'♻', U'⚜', U'🔱', U'📛', U'🔰', U'⭕', U'✅', U'☑', U'✔', U'❌', U'❎', U'➰', U'➿', U'〽', U'✳', U'✴', U'❇', U'©', U'®', U'™', U'🔟', U'🔠', U'🔡', U'🔢', U'🔣', U'🔤', U'🅰', U'🆎', U'🅱', U'🆑', U'🆒', U'🆓', U'ℹ', U'🆔', U'Ⓜ', U'🆕', U'🆖', U'🅾', U'🆗', U'🅿', U'🆘', U'🆙', U'🆚', U'🈁', U'🈂', U'🈷', U'🈶', U'🈯', U'🉐', U'🈹', U'🈚', U'🈲', U'🉑', U'🈸', U'🈴', U'🈳', U'㊗', U'㊙', U'🈺', U'🈵', U'🔴', U'🟠', U'🟡', U'🟢', U'🔵', U'🟣', U'🟤', U'⚫', U'⚪', U'🟥', U'🟧', U'🟨', U'🟩', U'🟦', U'🟪', U'🟫', U'⬛', U'⬜', U'◼', U'◻', U'◾', U'◽', U'▪', U'▫', U'🔶', U'🔷', U'🔸', U'🔹', U'🔺', U'🔻', U'💠', U'🔘', U'🔳', U'🔲', U'🏁', U'🚩', U'🎌', U'🏴', U'🏳'};
</code></pre>


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
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/win11_emj.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/win10.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/win8_emj.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/win7_emj.png"></td>
    <td><img src="https://github.com/SevRyb/Pinpoint/blob/main/showcase/win7-with-font_emj.png"></td>
  </tr>
</table>
<h2> TODO </h2>
<p>First of all implement encryption and multithreading on the server.</p>
