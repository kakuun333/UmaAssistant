using DiscordRPC;
using DiscordRPC.Logging;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading.Tasks;

namespace UmaCSharp
{
    public static class UmaLog
    {
        public static void d(string tag, string message)
        {
            Console.WriteLine(string.Format("[{0}][DEBUG] {1}", tag, message));
        }
    }

    public class FileManager
    {
        private static FileManager _instance = null;
        private static readonly object _lock = new object();
        private FileManager() { }
        public static FileManager Instance
        {
            get
            {
                if (_instance == null)
                {
                    lock (_lock) { if (_instance == null) _instance = new FileManager(); }
                }
                return _instance;
            }
        }
        // ========================================================== //
        private const string TAG = "FileManager";
        public string ReadFile(string path)
        {
            string fileContent = String.Empty;

            try
            {
                fileContent = File.ReadAllText(path);
                return fileContent;
            }
            catch (FileNotFoundException)
            { UmaLog.d(TAG, "JSON 檔案未找到。"); }
            catch (Exception ex)
            { UmaLog.d(TAG, "發生錯誤：" + ex.Message); }

            return fileContent;
        }
    }

    public class UmaDiscordManager
    {
        private static UmaDiscordManager _instance = null;
        private static readonly object _lock = new object();
        private UmaDiscordManager() {}
        public static UmaDiscordManager Instance
        {
            get
            {
                if (_instance == null)
                {
                    lock (_lock) { if (_instance == null) _instance = new UmaDiscordManager(); }
                }
                return _instance;
            }
        }
        // ========================================================== //
        private enum GameServerType
        {
            JP = 0,
            TW = 1,
        }

        private enum SoftwareLanguage
        {
            JP = 0,
            TW = 1,
        }

        #region constants
        private const string TAG = "DiscordManager";
        private const string JP_APP_CLIENT_ID = "1195236155709468752";
        private const string TW_APP_CLIENT_ID = "1195259431106138132";
        private const string LARGE_IMAGE_URL = "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaAssistant/UmaMisc/Image/DiscordRPC/umamusume_icon.png";
        private const string CHARACTER_ICON_URL = "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaAssistant/UmaMisc/Image/Character/";
        private const string JP_LARGE_IMAGE_TEXT = "ウマ娘 プリティーダービー";
        private const string TW_LARGE_IMAGE_TEXT = "賽馬娘 Pretty Derby";
        #endregion

        #region fields
        private string m_characterSmallIconUrl = string.Empty;
        #endregion

        #region properties
        public string CharacterSmallIconUrl
        {
            get { return m_characterSmallIconUrl; }
            private set { }
        }
        #endregion

        // DiscordRpcClient
        private DiscordRpcClient client;

        /// <summary>
        /// 從 select_character_data.json 獲取 CurrentCharacter 對應的圖片 URL
        /// 例如：https://raw.githubusercontent.com/../UmaMisc/Image/Character/i_123.png
        /// </summary>
        /// <param name="currentCharacterName"></param>
        /// <returns></returns>
        public void SetCharacterSmallIconUrl(string currentCharacterName)
        {
            string iconName = string.Empty;

            string selectCharacterDataPath = Directory.GetCurrentDirectory() + "/UmaData/select_character_data.json";
            string jsonContent = FileManager.Instance.ReadFile(selectCharacterDataPath);
            JArray jarr = JArray.Parse(jsonContent);

            foreach (var entry in jarr)
            {
                if (currentCharacterName == (string)entry["jp_event_owner"] || currentCharacterName == (string)entry["tw_event_owner"])
                {
                    iconName = (string)entry["icon"];
                    break;
                }
            }

            m_characterSmallIconUrl = CHARACTER_ICON_URL + iconName;
        }

        /// <summary>
        /// 初始化 DiscrdRpcClient
        /// 在程式結束之前需要調用 DiscordManager.Deinitialize() 告訴 Discord 結束 RPC
        /// 否則會導致 memory leak
        /// </summary>
        /// <param name="gameServer"></param>
        public void Initialize(int gameServer)
        {
            switch (gameServer)
            {
                case (int)GameServerType.JP:
                    client = new DiscordRpcClient(JP_APP_CLIENT_ID);
                    break;
                case (int)GameServerType.TW:
                    client = new DiscordRpcClient(TW_APP_CLIENT_ID);
                    break;
            }

            // Set the logger
            client.Logger = new ConsoleLogger() { Level = LogLevel.Warning };

            // Subscribe to events
            client.OnReady += (sender, e) =>
            {
                UmaLog.d(TAG, "已收到使用者的就緒訊息: " + e.User.Username);
            };

            client.OnPresenceUpdate += (sender, e) =>
            {
                UmaLog.d(TAG, "收到更新！ " + e.Presence);
            };

            // Connect to the RPC
            client.Initialize();
        }

        /// <summary>
        /// 去初始化 DiscrdRpcClient
        /// </summary>
        public void Deinitialize()
        {
            client.Dispose();
        }

        /// <summary>
        /// 設置 Rich Presence 的資訊
        /// 可以多次在程式碼中的任意位置調用
        /// </summary>
        /// <param name="gameServer"></param>
        /// <param name="largeImageUrl"></param>
        /// <param name="smallImageUrl"></param>
        public void SetPresence(int gameServer, int softwareLanguage, string currentCharacterName)
        {
            string _largeImageText = string.Empty;
            string _smallImageText = string.Empty;
            string _details = string.Empty;
            string _state = string.Empty;

            switch (gameServer)
            {
                case (int)GameServerType.JP:
                    _largeImageText = JP_LARGE_IMAGE_TEXT;
                    _smallImageText = string.IsNullOrEmpty(currentCharacterName) ? string.Empty : currentCharacterName;
                    _state          = string.Empty; // TODO: 顯示培育中的日期
                    break;
                case (int)GameServerType.TW:
                    _largeImageText = TW_LARGE_IMAGE_TEXT;
                    _smallImageText = string.IsNullOrEmpty(currentCharacterName) ? string.Empty : currentCharacterName;
                    _state          = string.Empty; // TODO: 顯示培育中的日期
                    break;
            }

            switch (softwareLanguage)
            {
                case (int)SoftwareLanguage.JP:
                    _details = string.IsNullOrEmpty(currentCharacterName) ? string.Empty : string.Format("{0} を育成している", currentCharacterName);
                    break;
                
                case (int)SoftwareLanguage.TW:
                    _details = string.IsNullOrEmpty(currentCharacterName) ? string.Empty : string.Format("培育 {0} 中", currentCharacterName);
                    break;
            }

            //Set the rich presence
            //Call this as many times as you want and anywhere in your code.
            client.SetPresence(new RichPresence()
            {
                Details = _details,
                State = _state,
                Assets = new Assets()
                {
                    LargeImageKey = LARGE_IMAGE_URL,
                    LargeImageText = _largeImageText,
                    SmallImageKey = m_characterSmallIconUrl,
                    SmallImageText = _smallImageText,
                }
            });
        }

        /// <summary>
        /// 更新 Presence
        /// </summary>
        public void Update()
        {
            //Invoke all the events, such as OnPresenceUpdate
            client.Invoke();
        }
    }
}
