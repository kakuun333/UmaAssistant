interface IRaceInfoItem
{
    imgSrc: string;
    raceName: string;
    raceDateGrade: string;
    raceDateDay: string;
    raceGrade: string;
    racecourse: string;
    raceTrack: string;
    raceDirection: string;
    raceDistanceType: string;
    raceDistance: string;
}

// TODO: 創建 raceInfoItem
function createRaceInfoItem(raceInfo: IRaceInfoItem): void
{
    const raceInfoItem = document.createElement("tr");
    raceInfoItem.className = "raceInfoItem";

    raceInfoItem.innerHTML =
    `
    <td>
        <input type="checkbox" name="raceInfoItemCheckbox">
        <img class="raceInfoItem_img" src="${raceInfo.imgSrc}"/>
        <div class="raceInfoItem_raceName">${raceInfo.raceName}</div>
    </td>
    <td class="raceInfoItem_raceDateGrade">${raceInfo.raceDateGrade}</td>
    <td class="raceInfoItem_raceDateDay">${raceInfo.raceDateDay}</td>
    <td class="raceInfoItem_raceGrade">${raceInfo.raceGrade}</td>
    <td class="raceInfoItem_racecourse">${raceInfo.racecourse}</td>
    <td class="raceInfoItem_raceTrack">${raceInfo.raceTrack}</td>
    <td class="raceInfoItem_raceDirection">${raceInfo.raceDirection}</td>
    <td class="raceInfoItem_raceDistanceType">${raceInfo.raceDistanceType}</td>
    <td class="raceInfoItem_raceDistance">${raceInfo.raceDistance}</td>
    `

    const raceInfoTable_tbody = document.getElementById("raceInfoTable_tbody")!;
    raceInfoTable_tbody.appendChild(raceInfoItem);
}

function setupFilterRadioButton(filterConfig: FilterConfig): void
{
    const filterRadioButtonList = document.querySelectorAll<HTMLInputElement>(".filter_radioButton");
    filterRadioButtonList.forEach((radioButton) => {
        radioButton.addEventListener("change", (event) => {
            if (radioButton.checked)
            {
                switch (radioButton.name)
                {
                case FilterType.RaceTrack:
                    filterConfig.RaceTrack.set(radioButton.value, true);
                    break;
                case FilterType.RaceDistanceType:
                    filterConfig.RaceDistanceType.set(radioButton.value, true);
                    break;
                case FilterType.RaceGrade:
                    filterConfig.RaceGrade.set(radioButton.value, true);
                    break;
                case FilterType.Racecourse:
                    filterConfig.Racecourse.set(radioButton.value, true);
                    break;
                }
            }
            else
            {
                switch (radioButton.name)
                {
                case FilterType.RaceTrack:
                    filterConfig.RaceTrack.set(radioButton.value, false);
                    break;
                case FilterType.RaceDistanceType:
                    filterConfig.RaceDistanceType.set(radioButton.value, false);
                    break;
                case FilterType.RaceGrade:
                    filterConfig.RaceGrade.set(radioButton.value, false);
                    break;
                case FilterType.Racecourse:
                    filterConfig.Racecourse.set(radioButton.value, false);
                    break;
                }
            }

            updateRaceInfoItemElementDisplay(filterConfig);
            console.log(filterConfig);
        })
    })
}

function setupEventListenerToRaceInfoItem(selectedRaceList: Array<Element>): void
{
    const raceInfoItemList = document.querySelectorAll<HTMLTableRowElement>(".raceInfoItem");

    raceInfoItemList.forEach((raceInfoItem) => {

        raceInfoItem.addEventListener("click", () => {
            const checkbox_list = raceInfoItem.querySelectorAll("input[type='checkbox']");
            const checkbox = checkbox_list[0] as HTMLInputElement;

            // TODO: 切換 checked
            checkbox.checked = !checkbox.checked;

            // TODO: 依照 checked 改變背景顏色
            // raceInfoItem.style.border = '2px solid red'
            raceInfoItem.style.background = checkbox.checked ? UmaColor.UMA_DARK_PURPLE : "";

            if (checkbox.checked)
            {
                selectedRaceList.push(raceInfoItem);
            }
            else
            {
                const itemIdx = selectedRaceList.indexOf(raceInfoItem);
                selectedRaceList.splice(itemIdx, 1);
            }
        })
    });
}

// TODO: 改變語言
function setRaceScheduleLanguage(language: SoftwareLanguage | AndroidLocale): void
{
    // start filterTitle
    const filterTitle_raceTrack = document.getElementById("filterTitle_raceTrack")!;
    const filterTitle_distanceType = document.getElementById("filterTitle_distanceType")!;
    const filterTitle_grade = document.getElementById("filterTitle_grade")!;
    const filterTitle_racecourse = document.getElementById("filterTitle_racecourse")!;
    // end filterTitle

    // start filterRadio
    const filterRadio_turf = document.getElementById("filterRadio_turf")!;
    const filterRadio_dirt = document.getElementById("filterRadio_dirt")!;
    const filterRadio_sprint = document.getElementById("filterRadio_sprint")!;
    const filterRadio_mile = document.getElementById("filterRadio_mile")!;
    const filterRadio_middle = document.getElementById("filterRadio_middle")!;
    const filterRadio_long = document.getElementById("filterRadio_long")!;
    // end filterRadio

    // start raceInfoTitle
    const raceInfoTitle_raceName = document.getElementById("raceInfoTitle_raceName")!;
    const raceInfoTitle_raceDateGrade = document.getElementById("raceInfoTitle_raceDateGrade")!;
    const raceInfoTitle_raceDateDay = document.getElementById("raceInfoTitle_raceDateDay")!;
    const raceInfoTitle_raceGrade = document.getElementById("raceInfoTitle_raceGrade")!;
    const raceInfoTitle_racecourse = document.getElementById("raceInfoTitle_racecourse")!;
    const raceInfoTitle_raceTrack = document.getElementById("raceInfoTitle_raceTrack")!;
    const raceInfoTitle_raceDirection = document.getElementById("raceInfoTitle_raceDirection")!;
    const raceInfoTitle_raceDistanceType = document.getElementById("raceInfoTitle_raceDistanceType")!;
    const raceInfoTitle_raceDistance = document.getElementById("raceInfoTitle_raceDistance")!;
    // end raceInfoTitle

    if (language == SoftwareLanguage.JP || language == AndroidLocale.JP)
    {
        // start filterTitle
        filterTitle_raceTrack.innerHTML = "バ場";
        filterTitle_distanceType.innerHTML = "距離";
        filterTitle_grade.innerHTML = "グレード";
        // filterTitle_racecourse.innerHTML = "レース場";
        // end filterTitle

        // start filterRadio
        filterRadio_turf.innerHTML = "芝";
        filterRadio_dirt.innerHTML = "ダート";

        filterRadio_sprint.innerHTML = "短距離"
        filterRadio_mile.innerHTML = "マイル"
        filterRadio_middle.innerHTML = "中距離"
        filterRadio_long.innerHTML = "長距離"
        // end filterRadio

        // start raceInfoTitle
        raceInfoTitle_raceName.innerHTML = "名称";
        raceInfoTitle_raceDateGrade.innerHTML = "年齢グレード";
        raceInfoTitle_raceDateDay.innerHTML = "期日";
        raceInfoTitle_raceGrade.innerHTML = "グレード";
        raceInfoTitle_racecourse.innerHTML = "レース場";
        raceInfoTitle_raceTrack.innerHTML = "バ場";
        raceInfoTitle_raceDirection.innerHTML = "方向";
        raceInfoTitle_raceDistanceType.innerHTML = "距離区分";
        raceInfoTitle_raceDistance.innerHTML = "距離";
        // end raceInfoTitle
    }
    else if (language == SoftwareLanguage.TW || language == AndroidLocale.TW)
    {
        // TODO: 翻譯繁體中文
    }
    else if (language == SoftwareLanguage.EN || language == AndroidLocale.EN)
    {
        // TODO: 翻譯英文
    }
}


// ========== Start Execute ========== //
const filterConfig = new FilterConfig();

const selectedRaceList = new Array<Element>();

// const raceInfoItemList = new Array<IRaceInfoItem>();



if (isWindowsDevice())
{
    readJson("../UmaData/race_data_jp.json", (jsonData: string) => {
        race_data_jp = jsonData;
    });
}

function reflushRaceItem(): void
{
    for (let index = 0; index < race_data_jp.length; index++)
    {
        const race_obj = race_data_jp[index];

        const raceInfoItem: IRaceInfoItem =
        {
            imgSrc: `../UmaMisc/Image/Race/${race_obj["race_image_name"]}`,
            raceName: race_obj["race_name"],
            raceDateGrade: race_obj["race_date_grade"],
            raceDateDay: race_obj["race_date_day"],
            raceGrade: race_obj["race_grade"],
            racecourse: race_obj["racecourse"],
            raceTrack: race_obj["race_track"],
            raceDirection: race_obj["race_direction"],
            raceDistanceType: race_obj["race_distance_type"],
            raceDistance: race_obj["race_distance"],
        }
        // raceInfoItemList.push(raceInfoItem);

        createRaceInfoItem(raceInfoItem);
    }
    
    updateRaceInfoItemElementDisplay(filterConfig);

    setupEventListenerToRaceInfoItem(selectedRaceList);
}

function loadJsonData(): void
{
    if (isWindowsDevice())
    {
        if (race_data_jp === null)
        {
            console.log("Loading json data...");
            setTimeout(loadJsonData, 100);
        }
        else
        {
            console.log("Loaded json data !!");

            reflushRaceItem();
        }
    }
}

setupFilterRadioButton(filterConfig);

setRaceScheduleLanguage(SoftwareLanguage.JP);

loadJsonData();


// alert("此功能目前僅支援日服");

function setSaveLoadRaceScheduleButton(): void
{
    const saveRaceScheduleButton = document.getElementById("saveRaceScheduleButton")! as HTMLButtonElement;
    const saveFileNameInput = document.getElementById("saveFileNameInput")! as HTMLInputElement;
    saveRaceScheduleButton.addEventListener("click", (event) => {
        
        if (saveFileNameInput.value === "") { alert("請輸入檔案名稱"); return; }

        const raceObjList = new Array<Object>();

        for (let element of selectedRaceList)
        {
            const raceNameElement = element.querySelector(".raceInfoItem_raceName")!;
            const raceDateGradeElement = element.querySelector(".raceInfoItem_raceDateGrade")!;
            const raceDateDayElement = element.querySelector(".raceInfoItem_raceDateDay")!;
            const raceGradeElement = element.querySelector(".raceInfoItem_raceGrade")!;
            const racecourseElement = element.querySelector(".raceInfoItem_racecourse")!;
            const raceTrackElement = element.querySelector(".raceInfoItem_raceTrack")!;
            const raceDirectionElement = element.querySelector(".raceInfoItem_raceDirection")!;
            const raceDistanceTypeElement = element.querySelector(".raceInfoItem_raceDistanceType")!;
            const raceDistanceElement = element.querySelector(".raceInfoItem_raceDistance")!;

            const raceObj =
            {
                race_name: raceNameElement.textContent,
                race_date_grade: raceDateGradeElement.textContent,
                race_date_day: raceDateDayElement.textContent,
                race_grade: raceGradeElement.textContent,
                racecourse: racecourseElement.textContent,
                race_track: raceTrackElement.textContent,
                race_direction: raceDirectionElement.textContent,
                race_distance_type: raceDistanceTypeElement.textContent,
                race_distance: raceDistanceElement.textContent,
            }

            raceObjList.push(raceObj);
        }

        
        const msgObj =
        {
            messageType: MessageType.SAVE_RACE_SCHEDULE_DATA,
            messageContent: {
                fileName: `${saveFileNameInput.value}.json`,
                raceObjectList: raceObjList,
            }
        }


        if (isWindowsDevice())
        {
            // @ts-ignore
            window.chrome.webview.postMessage(JSON.stringify(msgObj));
        }
    });


    // ==================== loadRaceScheduleButton ==================== //
    const loadRaceScheduleButton = document.getElementById("loadRaceScheduleButton")! as HTMLButtonElement;
    const loadRaceScheduleInput = document.getElementById("loadRaceScheduleInput")! as HTMLInputElement;

    loadRaceScheduleButton.addEventListener("click", () => {
        const file = loadRaceScheduleInput.files![0]; // 獲取選擇的檔案

        if (!file) { alert("請選擇檔案"); return; }
        
        const reader = new FileReader();
        // 監聽 FileReader 的 onload 事件
        reader.onload = (event) => {
            const fileContent = event.target!.result as string; // 獲取檔案內容
            
            const msgObj =
            {
                messageType: MessageType.LOAD_RACE_SCHEDULE_DATA,
                messageContent: fileContent,
            }

            // @ts-ignore
            window.chrome.webview.postMessage(JSON.stringify(msgObj));
        };
        reader.readAsText(file); // 讀取檔案內容
    });
}

setSaveLoadRaceScheduleButton();


disableContextMenu();
// ========== End Execute ========== //