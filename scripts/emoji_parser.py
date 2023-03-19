from bs4 import BeautifulSoup
import requests

page = requests.get("https://unicode.org/emoji/charts/full-emoji-list.html")

with open("index.html", "w", encoding="utf-8") as f:
    f.write(page.text)

soup = BeautifulSoup(page.text, 'html.parser')

emoji = []
emojies = []
data = []
table_body = soup.find('table')
rows = table_body.find_all('tr')
matches = True

for row in rows[3:]:
    cols = row.find_all('td')
    for col in cols:
        class_property = col.get("class")
        if class_property[0] == "code":
            if " " in col.find("a").text:
                break
            emoji.append(col.find("a").get("name"))
        elif class_property[0] == "chars":
            emoji.append(col.text)
   
    emojies.append(emoji.copy())
    emoji.clear()

n_in_line = 0
count = 0

c_array = "const char32_t emojies[] = {"
for e in emojies:
    if len(e) != 2:
        continue

    if n_in_line == 12:
        c_array += f"U'{e[1]}',\n"
        n_in_line = 0
    else:
        c_array += f"U'{e[1]}', "

    n_in_line += 1
    count += 1

c_array = c_array[:len(c_array)-2]
c_array += "};"

with open("emojies.cpp", "w", encoding="utf8") as file:
    file.write(c_array)
