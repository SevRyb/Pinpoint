#include <QPushButton>
#include <QLabel>
#include <QByteArray>
#include <QDebug>
#include <QFont>
#include "emojiwindow.h"

const char32_t emojies[] = {U'😀', U'😃', U'😄', U'😁', U'😆', U'😅', U'🤣', U'😂', U'🙂', U'🙃', U'😉', U'😊', U'😇', U'🥰', U'😍', U'🤩', U'😘', U'😗', U'😚', U'😙', U'😋', U'😛', U'😜', U'🤪', U'😝', U'🤑', U'🤗', U'🤭', U'🤫', U'🤔', U'🤐', U'🤨', U'😐', U'😑', U'😶', U'😏', U'😒', U'🙄', U'😬', U'🤥', U'😌', U'😔', U'😪', U'🤤', U'😴', U'😷', U'🤒', U'🤕', U'🤢', U'🤮', U'🤧', U'🥵', U'🥶', U'🥴', U'😵', U'🤯', U'🤠', U'🥳', U'😎', U'🤓', U'🧐', U'😕', U'😟', U'🙁', U'☹', U'😮', U'😯', U'😲', U'😳', U'🥺', U'😦', U'😧', U'😨', U'😰', U'😥', U'😢', U'😭', U'😱', U'😖', U'😣', U'😞', U'😓', U'😩', U'😫', U'🥱', U'😤', U'😡', U'😠', U'🤬', U'😈', U'👿', U'💀', U'☠', U'💩', U'🤡', U'👹', U'👺', U'👻', U'👽', U'👾', U'🤖', U'😺', U'😸', U'😹', U'😻', U'😼', U'😽', U'🙀', U'😿', U'😾', U'🙈', U'🙉', U'🙊', U'💋', U'💌', U'💘', U'💝', U'💖', U'💗', U'💓', U'💞', U'💕', U'💟', U'❣', U'💔', U'❤', U'🧡', U'💛', U'💚', U'💙', U'💜', U'🤎', U'🖤', U'🤍', U'💯', U'💢', U'💥', U'💫', U'💦', U'💨', U'🕳', U'💣', U'💬', U'🗨', U'🗯', U'💭', U'💤', U'👋', U'🤚', U'🖐', U'✋', U'🖖', U'👌', U'🤏', U'✌', U'🤞', U'🤟', U'🤘', U'🤙', U'👈', U'👉', U'👆', U'🖕', U'👇', U'☝', U'👍', U'👎', U'✊', U'👊', U'🤛', U'🤜', U'👏', U'🙌', U'👐', U'🤲', U'🤝', U'🙏', U'✍', U'💅', U'🤳', U'💪', U'🦾', U'🦿', U'🦵', U'🦶', U'👂', U'🦻', U'👃', U'🧠', U'🦷', U'🦴', U'👀', U'👁', U'👅', U'👄', U'👶', U'🧒', U'👦', U'👧', U'🧑', U'👱', U'👨', U'🧔', U'👩', U'🧓', U'👴', U'👵', U'🙍', U'🙎', U'🙅', U'🙆', U'💁', U'🙋', U'🧏', U'🙇', U'🤦', U'🤷', U'👮', U'🕵', U'💂', U'👷', U'🤴', U'👸', U'👳', U'👲', U'🧕', U'🤵', U'👰', U'🤰', U'🤱', U'👼', U'🎅', U'🤶', U'🦸', U'🦹', U'🧙', U'🧚', U'🧛', U'🧜', U'🧝', U'🧞', U'🧟', U'💆', U'💇', U'🚶', U'🧍', U'🧎', U'🏃', U'💃', U'🕺', U'🕴', U'👯', U'🧖', U'🧗', U'🤺', U'🏇', U'⛷', U'🏂', U'🏌', U'🏄', U'🚣', U'🏊', U'⛹', U'🏋', U'🚴', U'🚵', U'🤸', U'🤼', U'🤽', U'🤾', U'🤹', U'🧘', U'🛀', U'🛌', U'👭', U'👫', U'👬', U'💏', U'💑', U'👪', U'🗣', U'👤', U'👥', U'👣', U'🦰', U'🦱', U'🦳', U'🦲', U'🐵', U'🐒', U'🦍', U'🦧', U'🐶', U'🐕', U'🦮', U'🐩', U'🐺', U'🦊', U'🦝', U'🐱', U'🐈', U'🦁', U'🐯', U'🐅', U'🐆', U'🐴', U'🐎', U'🦄', U'🦓', U'🦌', U'🐮', U'🐂', U'🐃', U'🐄', U'🐷', U'🐖', U'🐗', U'🐽', U'🐏', U'🐑', U'🐐', U'🐪', U'🐫', U'🦙', U'🦒', U'🐘', U'🦏', U'🦛', U'🐭', U'🐁', U'🐀', U'🐹', U'🐰', U'🐇', U'🐿', U'🦔', U'🦇', U'🐻', U'🐨', U'🐼', U'🦥', U'🦦', U'🦨', U'🦘', U'🦡', U'🐾', U'🦃', U'🐔', U'🐓', U'🐣', U'🐤', U'🐥', U'🐦', U'🐧', U'🕊', U'🦅', U'🦆', U'🦢', U'🦉', U'🦩', U'🦚', U'🦜', U'🐸', U'🐊', U'🐢', U'🦎', U'🐍', U'🐲', U'🐉', U'🦕', U'🦖', U'🐳', U'🐋', U'🐬', U'🐟', U'🐠', U'🐡', U'🦈', U'🐙', U'🐚', U'🐌', U'🦋', U'🐛', U'🐜', U'🐝', U'🐞', U'🦗', U'🕷', U'🕸', U'🦂', U'🦟', U'🦠', U'💐', U'🌸', U'💮', U'🏵', U'🌹', U'🥀', U'🌺', U'🌻', U'🌼', U'🌷', U'🌱', U'🌲', U'🌳', U'🌴', U'🌵', U'🌾', U'🌿', U'☘', U'🍀', U'🍁', U'🍂', U'🍃', U'🍇', U'🍈', U'🍉', U'🍊', U'🍋', U'🍌', U'🍍', U'🥭', U'🍎', U'🍏', U'🍐', U'🍑', U'🍒', U'🍓', U'🥝', U'🍅',  U'🥥', U'🥑', U'🍆', U'🥔', U'🥕', U'🌽', U'🌶', U'🥒', U'🥬', U'🥦', U'🧄', U'🧅', U'🍄', U'🥜', U'🌰', U'🍞', U'🥐', U'🥖', U'🥨', U'🥯', U'🥞', U'🧇', U'🧀', U'🍖', U'🍗', U'🥩', U'🥓', U'🍔', U'🍟', U'🍕', U'🌭', U'🥪', U'🌮', U'🌯', U'🥙', U'🧆', U'🥚', U'🍳', U'🥘', U'🍲', U'🥣', U'🥗', U'🍿', U'🧈', U'🧂', U'🥫', U'🍱', U'🍘', U'🍙', U'🍚', U'🍛', U'🍜', U'🍝', U'🍠', U'🍢', U'🍣', U'🍤', U'🍥', U'🥮', U'🍡', U'🥟', U'🥠', U'🥡', U'🦀', U'🦞', U'🦐', U'🦑', U'🦪', U'🍦', U'🍧', U'🍨', U'🍩', U'🍪', U'🎂', U'🍰', U'🧁', U'🥧', U'🍫', U'🍬', U'🍭', U'🍮', U'🍯', U'🍼', U'🥛', U'☕', U'🍵', U'🍶', U'🍾', U'🍷', U'🍸', U'🍹', U'🍺', U'🍻', U'🥂', U'🥃', U'🥤', U'🧃', U'🧉', U'🧊', U'🥢', U'🍽', U'🍴', U'🥄', U'🔪', U'🏺', U'🌍', U'🌎', U'🌏', U'🌐', U'🗺', U'🗾', U'🧭', U'🏔', U'⛰', U'🌋', U'🗻', U'🏕', U'🏖', U'🏜', U'🏝', U'🏞', U'🏟', U'🏛', U'🏗', U'🧱', U'🏘', U'🏚', U'🏠', U'🏡', U'🏢', U'🏣', U'🏤', U'🏥', U'🏦', U'🏨', U'🏩', U'🏪', U'🏫', U'🏬', U'🏭', U'🏯', U'🏰', U'💒', U'🗼', U'🗽', U'⛪', U'🕌', U'🛕', U'🕍', U'⛩', U'🕋', U'⛲', U'⛺', U'🌁', U'🌃', U'🏙', U'🌄', U'🌅', U'🌆', U'🌇', U'🌉', U'♨', U'🎠', U'🎡', U'🎢', U'💈', U'🎪', U'🚂', U'🚃', U'🚄', U'🚅', U'🚆', U'🚇', U'🚈', U'🚉', U'🚊', U'🚝', U'🚞', U'🚋', U'🚌', U'🚍', U'🚎', U'🚐', U'🚑', U'🚒', U'🚓', U'🚔', U'🚕', U'🚖', U'🚗', U'🚘', U'🚙', U'🚚', U'🚛', U'🚜', U'🏎', U'🏍', U'🛵', U'🦽', U'🦼', U'🛺', U'🚲', U'🛴', U'🛹', U'🚏', U'🛣', U'🛤', U'🛢', U'⛽', U'🚨', U'🚥', U'🚦', U'🛑', U'🚧', U'⚓', U'⛵', U'🛶', U'🚤', U'🛳', U'⛴', U'🛥', U'🚢', U'✈', U'🛩', U'🛫', U'🛬', U'🪂', U'💺', U'🚁', U'🚟', U'🚠', U'🚡', U'🛰', U'🚀', U'🛸', U'🛎', U'🧳', U'⌛', U'⏳', U'⌚', U'⏰', U'⏱', U'⏲', U'🕰', U'🕛', U'🕧', U'🕐', U'🕜', U'🕑', U'🕝', U'🕒', U'🕞', U'🕓', U'🕟', U'🕔', U'🕠', U'🕕', U'🕡', U'🕖', U'🕢', U'🕗', U'🕣', U'🕘', U'🕤', U'🕙', U'🕥', U'🕚', U'🕦', U'🌑', U'🌒', U'🌓', U'🌔', U'🌕', U'🌖', U'🌗', U'🌘', U'🌙', U'🌚', U'🌛', U'🌜', U'🌡', U'☀', U'🌝', U'🌞', U'🪐', U'⭐', U'🌟', U'🌠', U'🌌', U'☁', U'⛅', U'⛈', U'🌤', U'🌥', U'🌦', U'🌧', U'🌨', U'🌩', U'🌪', U'🌫', U'🌬', U'🌀', U'🌈', U'🌂', U'☂', U'☔', U'⛱', U'⚡', U'❄', U'☃', U'⛄', U'☄', U'🔥', U'💧', U'🌊', U'🎃', U'🎄', U'🎆', U'🎇', U'🧨', U'✨', U'🎈', U'🎉', U'🎊', U'🎋', U'🎍', U'🎎', U'🎏', U'🎐', U'🎑', U'🧧', U'🎀', U'🎁', U'🎗', U'🎟', U'🎫', U'🎖', U'🏆', U'🏅', U'🥇', U'🥈', U'🥉', U'⚽', U'⚾', U'🥎', U'🏀', U'🏐', U'🏈', U'🏉', U'🎾', U'🥏', U'🎳', U'🏏', U'🏑', U'🏒', U'🥍', U'🏓', U'🏸', U'🥊', U'🥋', U'🥅', U'⛳', U'⛸', U'🎣', U'🤿', U'🎽', U'🎿', U'🛷', U'🥌', U'🎯', U'🪀', U'🪁', U'🎱', U'🔮', U'🧿', U'🎮', U'🕹', U'🎰', U'🎲', U'🧩', U'🧸', U'♠', U'♥', U'♦', U'♣', U'♟', U'🃏', U'🀄', U'🎴', U'🎭', U'🖼', U'🎨', U'🧵', U'🧶', U'👓', U'🕶', U'🥽', U'🥼', U'🦺', U'👔', U'👕', U'👖', U'🧣', U'🧤', U'🧥', U'🧦', U'👗', U'👘', U'🥻', U'🩱', U'🩲', U'🩳', U'👙', U'👚', U'👛', U'👜', U'👝', U'🛍', U'🎒', U'👞', U'👟', U'🥾', U'🥿', U'👠', U'👡', U'🩰', U'👢', U'👑', U'👒', U'🎩', U'🎓', U'🧢', U'⛑', U'📿', U'💄', U'💍', U'💎', U'🔇', U'🔈', U'🔉', U'🔊', U'📢', U'📣', U'📯', U'🔔', U'🔕', U'🎼', U'🎵', U'🎶', U'🎙', U'🎚', U'🎛', U'🎤', U'🎧', U'📻', U'🎷', U'🎸', U'🎹', U'🎺', U'🎻', U'🪕', U'🥁', U'📱', U'📲', U'☎', U'📞', U'📟', U'📠', U'🔋', U'🔌', U'💻', U'🖥', U'🖨', U'⌨', U'🖱', U'🖲', U'💽', U'💾', U'💿', U'📀', U'🧮', U'🎥', U'🎞', U'📽', U'🎬', U'📺', U'📷', U'📸', U'📹', U'📼', U'🔍', U'🔎', U'🕯', U'💡', U'🔦', U'🏮', U'🪔', U'📔', U'📕', U'📖', U'📗', U'📘', U'📙', U'📚', U'📓', U'📒', U'📃', U'📜', U'📄', U'📰', U'🗞', U'📑', U'🔖', U'🏷', U'💰', U'💴', U'💵', U'💶', U'💷', U'💸', U'💳', U'🧾', U'💹', U'✉', U'📧', U'📨', U'📩', U'📤', U'📥', U'📦', U'📫', U'📪', U'📬', U'📭', U'📮', U'🗳', U'✏', U'✒', U'🖋', U'🖊', U'🖌', U'🖍', U'📝', U'💼', U'📁', U'📂', U'🗂', U'📅', U'📆', U'🗒', U'🗓', U'📇', U'📈', U'📉', U'📊', U'📋', U'📌', U'📍', U'📎', U'🖇', U'📏', U'📐', U'✂', U'🗃', U'🗄', U'🗑', U'🔒', U'🔓', U'🔏', U'🔐', U'🔑', U'🗝', U'🔨', U'🪓', U'⛏', U'⚒', U'🛠', U'🗡', U'⚔', U'🔫', U'🏹', U'🛡', U'🔧', U'🔩', U'⚙', U'🗜', U'⚖', U'🦯', U'🔗', U'⛓', U'🧰', U'🧲', U'⚗', U'🧪', U'🧫', U'🧬', U'🔬', U'🔭', U'📡', U'💉', U'🩸', U'💊', U'🩹', U'🩺', U'🚪', U'🛏', U'🛋', U'🪑', U'🚽', U'🚿', U'🛁', U'🪒', U'🧴', U'🧷', U'🧹', U'🧺', U'🧻', U'🧼', U'🧽', U'🧯', U'🛒', U'🚬', U'⚰', U'⚱', U'🗿', U'🏧', U'🚮', U'🚰', U'♿', U'🚹', U'🚺', U'🚻', U'🚼', U'🚾', U'🛂', U'🛃', U'🛄', U'🛅', U'⚠', U'🚸', U'⛔', U'🚫', U'🚳', U'🚭', U'🚯', U'🚱', U'🚷', U'📵', U'🔞', U'☢', U'☣', U'⬆', U'↗', U'➡', U'↘', U'⬇', U'↙', U'⬅', U'↖', U'↕', U'↔', U'↩', U'↪', U'⤴', U'⤵', U'🔃', U'🔄', U'🔙', U'🔚', U'🔛', U'🔜', U'🔝', U'🛐', U'⚛', U'🕉', U'✡', U'☸', U'☯', U'✝', U'☦', U'☪', U'☮', U'🕎', U'🔯', U'♈', U'♉', U'♊', U'♋', U'♌', U'♍', U'♎', U'♏', U'♐', U'♑', U'♒', U'♓', U'⛎', U'🔀', U'🔁', U'🔂', U'▶', U'⏩', U'⏭', U'⏯', U'◀', U'⏪', U'⏮', U'🔼', U'⏫', U'🔽', U'⏬', U'⏸', U'⏹', U'⏺', U'⏏', U'🎦', U'🔅', U'🔆', U'📶', U'📳', U'📴', U'♀', U'♂', U'⚧', U'✖', U'➕', U'➖', U'➗', U'♾', U'‼', U'⁉', U'❓', U'❔', U'❕', U'❗', U'〰', U'💱', U'💲', U'⚕', U'♻', U'⚜', U'🔱', U'📛', U'🔰', U'⭕', U'✅', U'☑', U'✔', U'❌', U'❎', U'➰', U'➿', U'〽', U'✳', U'✴', U'❇', U'©', U'®', U'™', U'🔟', U'🔠', U'🔡', U'🔢', U'🔣', U'🔤', U'🅰', U'🆎', U'🅱', U'🆑', U'🆒', U'🆓', U'ℹ', U'🆔', U'Ⓜ', U'🆕', U'🆖', U'🅾', U'🆗', U'🅿', U'🆘', U'🆙', U'🆚', U'🈁', U'🈂', U'🈷', U'🈶', U'🈯', U'🉐', U'🈹', U'🈚', U'🈲', U'🉑', U'🈸', U'🈴', U'🈳', U'㊗', U'㊙', U'🈺', U'🈵', U'🔴', U'🟠', U'🟡', U'🟢', U'🔵', U'🟣', U'🟤', U'⚫', U'⚪', U'🟥', U'🟧', U'🟨', U'🟩', U'🟦', U'🟪', U'🟫', U'⬛', U'⬜', U'◼', U'◻', U'◾', U'◽', U'▪', U'▫', U'🔶', U'🔷', U'🔸', U'🔹', U'🔺', U'🔻', U'💠', U'🔘', U'🔳', U'🔲', U'🏁', U'🚩', U'🎌', U'🏴', U'🏳'};

EmojiWindow::EmojiWindow(QWidget *parent)
    : QWidget{parent}
{
    resize(300, 300);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    setWindowTitle(tr("Pinpoint - Emojies"));

    m_mainVBoxLay = new QVBoxLayout(this);
    m_mainVBoxLay->setContentsMargins(0, 0, 0, 0);
    setLayout(m_mainVBoxLay);

    m_gridLay = new QGridLayout;
    m_gridLay->setSpacing(0);

    m_scrollAreaContainer = new QWidget(this);
    m_scrollAreaContainer->setLayout(m_gridLay);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidget(m_scrollAreaContainer);

    m_mainVBoxLay->addWidget(m_scrollArea);

    int row = 0, column = 0;
    for (int i = 0; i < sizeof(emojies) / sizeof(emojies[0]); i++)
    {

        QPushButton *emoji_button = new QPushButton(QString::fromUcs4(emojies + i, 1), this);
        connect(emoji_button, &QPushButton::clicked, this, [this, emoji_button]()
        {
            emit insertEmoji(emoji_button->text());
        });
        m_gridLay->addWidget(emoji_button, row, column);
        column++;
        if (column == 7)
        {
            column = 0;
            row++;
        }
    }

    setStyleSheet("QWidget"
                  "{"
                    "background: rgba(37, 56, 88, 255);"
                    "color: rgba(125, 140, 165, 255);"
                    "border: none;"
                   "}"
                   "QPushButton"
                   "{"
                    "font-family: Segoe UI Emoji;"
                    "font-size: 25px;"
                    "color: white;"
                    "background: transparent;"
                    "border-radius: 4px;"
                   "}"
                   "QPushButton:hover"
                   "{"
                     "border: 1px solid rgb(7, 22, 44);"
                   "}"
                   "QPushButton:pressed"
                   "{"
                     "background: rgb(7, 22, 44);"
                   "}"
                   "QScrollBar:vertical"
                   "{"
                     "background-color: rgba(0, 0, 0, 50);"
                     "border-radius: 3px;"
                     "width: 7px;"
                     "margin: 2px 0px 2px 0px;"
                   "}"
                   "QScrollBar::handle:vertical"
                   "{"
                     "background-color: rgba(0, 0, 0, 40);"
                     "border-radius: 3px;"
                     "min-height: 20px;"
                     "max-height: 50px;"
                     "margin: 12px 0px 12px 0px;"
                   "}"
                   "QScrollBar::add-line:vertical"
                   "{"
                     "background: transparent;"
                     "border-radius: 0px;"
                     "border-bottom-left-radius: 3px;"
                     "border-bottom-right-radius: 3px;"
                     "height: 10px;"
                   "}"
                   "QScrollBar::sub-line:vertical"
                   "{"
                     "background: transparent;"
                     "border-radius: 0px;"
                     "border-top-left-radius: 3px;"
                     "border-top-right-radius: 3px;"
                     "height: 10px;"
                   "}"
                   "QScrollBar::up-arrow:vertical"
                   "{"
                     "background: none;"
                   "}"
                   "QScrollBar::down-arrow:vertical"
                   "{"
                     "background: none;"
                   "}"
                   "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical"
                   "{"
                     "background: none;"
                   "}");

}
//------------------------------------------------------------------------------------------
EmojiWindow::~EmojiWindow()
{
}
