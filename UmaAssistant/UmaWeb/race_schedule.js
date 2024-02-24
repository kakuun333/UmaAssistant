"use strict";
// TODO: 創建 raceInfoItem
function createRaceInfoItem(raceInfo) {
    var raceInfoItem = document.createElement("tr");
    raceInfoItem.className = "raceInfoItem";
    raceInfoItem.innerHTML =
        "\n    <td>\n        <input type=\"checkbox\" name=\"raceInfoItemCheckbox\" value=\"".concat(raceInfo.inputValue, "\">\n        <img class=\"raceInfoItem_img\" src=\"").concat(raceInfo.imgSrc, "\"/>\n        <div class=\"raceInfoItem_raceName\">").concat(raceInfo.raceName, "</div>\n    </td>\n    <td class=\"raceInfoItem_raceDateGrade\">").concat(raceInfo.raceDateGrade, "</td>\n    <td class=\"raceInfoItem_raceDateDay\">").concat(raceInfo.raceDateDay, "</td>\n    <td class=\"raceInfoItem_raceGrade\">").concat(raceInfo.raceGrade, "</td>\n    <td class=\"raceInfoItem_racecourse\">").concat(raceInfo.racecourse, "</td>\n    <td class=\"raceInfoItem_raceTrack\">").concat(raceInfo.raceTrack, "</td>\n    <td class=\"raceInfoItem_raceDirection\">").concat(raceInfo.raceDirection, "</td>\n    <td class=\"raceInfoItem_raceDistanceType\">").concat(raceInfo.raceDistanceType, "</td>\n    <td class=\"raceInfoItem_raceDistance\">").concat(raceInfo.raceDistance, "</td>\n    ");
    var raceInfoTable_tbody = document.getElementById("raceInfoTable_tbody");
    raceInfoTable_tbody.appendChild(raceInfoItem);
}
function setupFilterRadioButton(filterConfig) {
    var filterRadioButtonList = document.querySelectorAll(".filter_radioButton");
    filterRadioButtonList.forEach(function (radioButton) {
        radioButton.addEventListener("change", function (event) {
            if (radioButton.checked) {
                switch (radioButton.name) {
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
            else {
                switch (radioButton.name) {
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
        });
    });
}
function setupEventListenerToRaceInfoItem(selectedRaceList) {
    var raceInfoItemList = document.querySelectorAll(".raceInfoItem");
    raceInfoItemList.forEach(function (raceInfoItem) {
        raceInfoItem.addEventListener("click", function () {
            var checkbox_list = raceInfoItem.querySelectorAll("input[type='checkbox']");
            var checkbox = checkbox_list[0];
            // TODO: 切換 checked
            checkbox.checked = !checkbox.checked;
            // TODO: 依照 checked 改變背景顏色
            // raceInfoItem.style.border = '2px solid red'
            raceInfoItem.style.background = checkbox.checked ? UmaColor.UMA_DARK_PURPLE : "";
            if (checkbox.checked) {
                selectedRaceList.push(raceInfoItem);
            }
            else {
                var itemIdx = selectedRaceList.indexOf(raceInfoItem);
                selectedRaceList.splice(itemIdx, 1);
            }
        });
    });
}
// TODO: 改變語言
function setRaceScheduleLanguage(language) {
    // start filterTitle
    var filterTitle_raceTrack = document.getElementById("filterTitle_raceTrack");
    var filterTitle_distanceType = document.getElementById("filterTitle_distanceType");
    var filterTitle_grade = document.getElementById("filterTitle_grade");
    var filterTitle_racecourse = document.getElementById("filterTitle_racecourse");
    // end filterTitle
    // start filterRadio
    var filterRadio_turf = document.getElementById("filterRadio_turf");
    var filterRadio_dirt = document.getElementById("filterRadio_dirt");
    var filterRadio_sprint = document.getElementById("filterRadio_sprint");
    var filterRadio_mile = document.getElementById("filterRadio_mile");
    var filterRadio_middle = document.getElementById("filterRadio_middle");
    var filterRadio_long = document.getElementById("filterRadio_long");
    // end filterRadio
    // start raceInfoTitle
    var raceInfoTitle_raceName = document.getElementById("raceInfoTitle_raceName");
    var raceInfoTitle_raceDateGrade = document.getElementById("raceInfoTitle_raceDateGrade");
    var raceInfoTitle_raceDateDay = document.getElementById("raceInfoTitle_raceDateDay");
    var raceInfoTitle_raceGrade = document.getElementById("raceInfoTitle_raceGrade");
    var raceInfoTitle_racecourse = document.getElementById("raceInfoTitle_racecourse");
    var raceInfoTitle_raceTrack = document.getElementById("raceInfoTitle_raceTrack");
    var raceInfoTitle_raceDirection = document.getElementById("raceInfoTitle_raceDirection");
    var raceInfoTitle_raceDistanceType = document.getElementById("raceInfoTitle_raceDistanceType");
    var raceInfoTitle_raceDistance = document.getElementById("raceInfoTitle_raceDistance");
    // end raceInfoTitle
    if (language == SoftwareLanguage.JP || language == AndroidLocale.JP) {
        // start filterTitle
        filterTitle_raceTrack.innerHTML = "バ場";
        filterTitle_distanceType.innerHTML = "距離";
        filterTitle_grade.innerHTML = "グレード";
        // filterTitle_racecourse.innerHTML = "競馬場";
        // end filterTitle
        // start filterRadio
        filterRadio_turf.innerHTML = "芝";
        filterRadio_dirt.innerHTML = "ダート";
        filterRadio_sprint.innerHTML = "短距離";
        filterRadio_mile.innerHTML = "マイル";
        filterRadio_middle.innerHTML = "中距離";
        filterRadio_long.innerHTML = "長距離";
        // end filterRadio
        // start raceInfoTitle
        raceInfoTitle_raceName.innerHTML = "名称";
        raceInfoTitle_raceDateGrade.innerHTML = "年齢グレード";
        raceInfoTitle_raceDateDay.innerHTML = "期日";
        raceInfoTitle_raceGrade.innerHTML = "グレード";
        raceInfoTitle_racecourse.innerHTML = "競馬場";
        raceInfoTitle_raceTrack.innerHTML = "バ場";
        raceInfoTitle_raceDirection.innerHTML = "方向";
        raceInfoTitle_raceDistanceType.innerHTML = "距離区分";
        raceInfoTitle_raceDistance.innerHTML = "距離";
        // end raceInfoTitle
    }
    else if (language == SoftwareLanguage.TW || language == AndroidLocale.TW) {
        // TODO: 翻譯繁體中文
    }
    else if (language == SoftwareLanguage.EN || language == AndroidLocale.EN) {
        // TODO: 翻譯英文
    }
}
// ========== Start Execute ========== //
var filterConfig = new FilterConfig();
var selectedRaceList = new Array();
// const raceInfoItemList = new Array<IRaceInfoItem>();
if (isWindowsDevice()) {
    readJson("../UmaData/race_data_jp.json", function (jsonData) {
        race_data_jp = jsonData;
    });
}
function reflushRaceItem() {
    for (var index = 0; index < race_data_jp.length; index++) {
        var race_obj = race_data_jp[index];
        var raceInfoItem = {
            imgSrc: "../UmaMisc/Image/Race/".concat(race_obj["race_image_name"]),
            raceName: race_obj["race_name"],
            raceDateGrade: race_obj["race_date_grade"],
            raceDateDay: race_obj["race_date_day"],
            raceGrade: race_obj["race_grade"],
            racecourse: race_obj["racecourse"],
            raceTrack: race_obj["race_track"],
            raceDirection: race_obj["race_direction"],
            raceDistanceType: race_obj["race_distance_type"],
            raceDistance: race_obj["race_distance"],
            inputValue: index
        };
        // raceInfoItemList.push(raceInfoItem);
        createRaceInfoItem(raceInfoItem);
    }
    updateRaceInfoItemElementDisplay(filterConfig);
    setupEventListenerToRaceInfoItem(selectedRaceList);
}
function loadJsonData() {
    if (isWindowsDevice()) {
        if (race_data_jp === null) {
            console.log("Loading json data...");
            setTimeout(loadJsonData, 100);
        }
        else {
            console.log("Loaded json data !!");
            reflushRaceItem();
        }
    }
}
setupFilterRadioButton(filterConfig);
setRaceScheduleLanguage(SoftwareLanguage.JP);
loadJsonData();
// alert("此功能目前僅支援日服");
function setSaveLoadRaceScheduleButton() {
    var saveRaceScheduleButton = document.getElementById("saveRaceScheduleButton");
    saveRaceScheduleButton.addEventListener("click", function (event) {
        var tempArray = new Array();
        for (var _i = 0, selectedRaceList_1 = selectedRaceList; _i < selectedRaceList_1.length; _i++) {
            var element = selectedRaceList_1[_i];
            var raceNameElement = element.querySelector(".raceInfoItem_raceName");
            var raceDateGradeElement = element.querySelector(".raceInfoItem_raceDateGrade");
            var raceDateDayElement = element.querySelector(".raceInfoItem_raceDateDay");
            var raceGradeElement = element.querySelector(".raceInfoItem_raceGrade");
            var racecourseElement = element.querySelector(".raceInfoItem_racecourse");
            var raceTrackElement = element.querySelector(".raceInfoItem_raceTrack");
            var raceDirectionElement = element.querySelector(".raceInfoItem_raceDirection");
            var raceDistanceTypeElement = element.querySelector(".raceInfoItem_raceDistanceType");
            var raceDistanceElement = element.querySelector(".raceInfoItem_raceDistance");
            var msgObj = {
                messageType: MessageType.SAVE_RACE_SCHEDULE_DATA,
                race_name: raceNameElement.textContent,
                race_grade: raceDateGradeElement.textContent,
                race_track: raceDateDayElement.textContent,
                racecourse: raceGradeElement.textContent,
                race_distance: racecourseElement.textContent,
                race_distance_type: raceTrackElement.textContent,
                race_direction: raceDirectionElement.textContent,
                race_date_grade: raceDistanceTypeElement.textContent,
                race_date_day: raceDistanceElement.textContent,
            };
            tempArray.push(msgObj);
        }
        // @ts-ignore
        window.chrome.webview.postMessage(JSON.stringify(tempArray));
    });
}
setSaveLoadRaceScheduleButton();
// ========== End Execute ========== //
