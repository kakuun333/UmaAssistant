// 創建 choice
function createChoice(choice_title, choice_effect) {
    let choice_table = document.getElementById("choice_table");
    let tr = document.createElement("tr");
    let th = document.createElement("th");
    let td = document.createElement("td");
    th.innerHTML = choice_title;
    td.innerHTML = choice_effect;

    tr.appendChild(th);
    tr.appendChild(td);

    choice_table.appendChild(tr);
}

// 清除所有選項
function cleanChoiceTable() {
    let choice_table = document.getElementById("choice_table");
    while (choice_table.firstChild) {
        choice_table.removeChild(choice_table.firstChild);
    }
}

function changeEventTitle(text) {
    let event_title = document.getElementById("event_title");
    event_title.innerHTML = text;
}

function changeEventOwner(text) {
    let event_owner = document.getElementById("event_owner");
    event_owner.innerHTML = text;
}

createChoice("title", "effect<br>effect");
