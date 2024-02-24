// ========== start enum ========== //
enum FilterType
{
    RaceTrack = "raceTrack",
    RaceDistanceType = "distanceType",
    RaceGrade = "raceGrade",
    Racecourse = "racecourse"
}

enum RaceTrack
{
    Turf = "turf",
    Dirt = "dirt",
}

enum RaceDistanceType
{
    Sprint = "sprint",
    Mile = "mile",
    Middle = "middle",
    Long = "long"
}

enum RaceGrade
{
    GOne = "gOne",
    GTwo = "gTwo",
    GThree = "gThree",
    Op = "op",
    PreOp = "preOp",
}
// ========== end enum ========== //

interface IFilterConfig {
    RaceTrack: Map<string, boolean>,
    RaceDistanceType: Map<string, boolean>,
    RaceGrade: Map<string, boolean>,
    Racecourse: Map<string, boolean>,
}

function raceInfoTextToValue(text: string | null): string
{
    if (text === "芝") return RaceTrack.Turf;
    if (text === "ダート") return RaceTrack.Dirt;
    
    if (text === "短距離") return RaceDistanceType.Sprint;
    if (text === "マイル") return RaceDistanceType.Mile;
    if (text === "中距離") return RaceDistanceType.Middle;
    if (text === "長距離") return RaceDistanceType.Long;
    
    if (text === "G1") return RaceGrade.GOne;
    if (text === "G2") return RaceGrade.GTwo;
    if (text === "G3") return RaceGrade.GThree;
    if (text === "OP") return RaceGrade.Op;
    if (text === "Pre-OP") return RaceGrade.PreOp;
    
    return "";
}


function updateRaceInfoItemElementDisplay(filterConfig: FilterConfig): void
{
    const raceInfoItemList = document.querySelectorAll(".raceInfoItem")!;

    
    for (let i = 0; i < raceInfoItemList.length; i++)
    {
        const item = raceInfoItemList[i] as HTMLElement;
        const raceTrackElement = item.querySelector(".raceInfoItem_raceTrack")!;
        const raceDistanceTypeElement = item.querySelector(".raceInfoItem_raceDistanceType")!;
        const raceGradeElement = item.querySelector(".raceInfoItem_raceGrade")!;

        const raceTrack = raceInfoTextToValue(raceTrackElement.textContent);
        const raceDistanceType = raceInfoTextToValue(raceDistanceTypeElement.textContent);
        const raceGrade = raceInfoTextToValue(raceGradeElement.textContent);
        

        if (filterConfig.RaceTrack.get(raceTrack) &&
            filterConfig.RaceDistanceType.get(raceDistanceType) &&
            filterConfig.RaceGrade.get(raceGrade)
        )
        {
            item.style.display = "table-row"; // 顯示
        }
        else
        {
            item.style.display = "none"; // 不顯示
        }
    }
}

class FilterConfig implements IFilterConfig {
    private m_raceTrack: Map<string, boolean>;
    private m_raceDistanceType: Map<string, boolean>;
    private m_raceGrade: Map<string, boolean>;
    private m_racecourse: Map<string, boolean>;

    constructor()
    {
        this.m_raceTrack = new Map<string, boolean>();
        this.m_raceTrack.set(RaceTrack.Turf, false);
        this.m_raceTrack.set(RaceTrack.Dirt, false);

        this.m_raceDistanceType = new Map<string, boolean>();
        this.m_raceDistanceType.set(RaceDistanceType.Sprint, false);
        this.m_raceDistanceType.set(RaceDistanceType.Mile, false);
        this.m_raceDistanceType.set(RaceDistanceType.Middle, false);
        this.m_raceDistanceType.set(RaceDistanceType.Long, false);

        this.m_raceGrade = new Map<string, boolean>();
        this.m_raceGrade.set(RaceGrade.GOne, false);
        this.m_raceGrade.set(RaceGrade.GTwo, false);
        this.m_raceGrade.set(RaceGrade.GThree, false);
        this.m_raceGrade.set(RaceGrade.Op, false);
        this.m_raceGrade.set(RaceGrade.PreOp, false);

        this.m_racecourse = new Map<string, boolean>();
        // TODO: 初始化 Racecourse 的 Map
    }

    get RaceTrack(): Map<string, boolean> { return this.m_raceTrack; }
    set RaceTrack(value: Map<string, boolean>) { this.m_raceTrack = value; }

    get RaceDistanceType(): Map<string, boolean> { return this.m_raceDistanceType; }
    set RaceDistanceType(value: Map<string, boolean>) { this.m_raceDistanceType = value; }

    get RaceGrade(): Map<string, boolean> { return this.m_raceGrade; }
    set RaceGrade(value: Map<string, boolean>) { this.m_raceGrade = value; }

    get Racecourse(): Map<string, boolean> { return this.m_racecourse; }
    set Racecourse(value: Map<string, boolean>) { this.m_racecourse = value; }
}