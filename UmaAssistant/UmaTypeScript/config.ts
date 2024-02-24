const Config = {
    GameServer: GameServer.JP,
    JpServerLanguage: JpServerLanguage.JP,
}

function setGameServer(gameServer: GameServer) {
    Config.GameServer = gameServer;
}

function setJpServerLanguage(jpServerLanguage: JpServerLanguage) {
    Config.JpServerLanguage = jpServerLanguage;
}