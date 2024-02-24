const Config =
{
    GameServer: GameServer.JP,
    JpServerLanguage: JpServerLanguage.JP,
}

function setGameServer(gameServer: GameServer): void
{
    Config.GameServer = gameServer;
}

function setJpServerLanguage(jpServerLanguage: JpServerLanguage): void
{
    Config.JpServerLanguage = jpServerLanguage;
}