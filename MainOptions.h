#include "includes.h"

static ID3D11DeviceContext* m_pContext;
static ID3D11RenderTargetView* g_pRenderTargetView;
static IDXGISwapChain* g_pSwapChain;

static WNDPROC oWndProc;

typedef int (WINAPI* LPFN_MBA)(DWORD);
static LPFN_MBA o_getasynckeystate;


static HWND hWnd;
static int CurrentTab;

static bool ShowMenu = false;

static int AimBoneInt = 66;


typedef struct {
	
	bool AnnasMisc;
	bool MouseAim;
	bool AimHelper;
	bool Aimbot;
	bool FreeCam;
	bool FOVChanger;
	bool SniperHits;
	bool SilentAimbot;
	bool SniperThroughWalls;
	bool SniperNoAimbot;
	bool Crosshair;
	bool NoSpreadAimbot;
	float AimbotFOV;
	float AimbotSlow;
	bool InstantReload;
	float FOV;
	int AimPos; // head body dick
	int Aimkeypos; // the key
	int aimkey;
	int crosshairScale;
	float crosshairNuclear;
	bool isRecFov;
	bool visCheck;
	int OverallDistance;
	float SnaplinePower;
	bool ShowInfoBar;
	bool RadarESP;
	bool AirStuck;
	float RadarESPRange;
	bool WarningEnemiesArea;
	bool ClosestEnemyDistance;
	bool HelicopterInfiniteBoost;
	bool HelicopterSpeed;
	bool InvisiblePlayer;
	float HelicopterSpeedMultiplier;
	bool Dev;
	bool BoatBoost;
	float BoatBoostMultiplier;
	bool BoatTP;
	bool BoatFly;
	bool PlrTP;
	int AirStuckKey;
	bool RapidFire;
	int BoatTPkey;
	bool PlayerFly;
	bool WeakSpot;

	struct {
		bool AimbotFOV;
		bool Players;
		bool Distance;
		bool Skeleton;
		bool PlayerLines;
		bool Lazer;
		bool PlayerNames;
		bool PlayerWeapons;
		float PlayerVisibleColor[3];
		float PlayerNotVisibleColor[3];
		bool Ammo;
		bool Boats;
		bool Helicopters;
		bool Trucks;
		bool Taxi;
		bool Cars;
		bool Chests;
		bool AmmoBox;
		bool UpgradeBench;
		bool Llama;
		bool SupplyDrop;
		bool Weapons;
		bool Box;
		bool ThreeDBox;
		bool AgentsBoss;
		bool CornerBox;
		bool AimLine;
		bool Chams;
		bool Shark;
		bool RandomAim;
		bool XPCoin;
		INT MinWeaponTier;
	} ESP;
	struct {
		bool head;
		bool body;
		bool dick;
	} AimPosSt;
} SETTINGS;

SETTINGS Settings = { 0 };
namespace SettingsHelper {
	VOID Initialize() {
		Settings = { 0 };
	
		Settings.Aimbot = true;
		Settings.MouseAim = false;
		Settings.AimbotFOV = 50.5f;
		Settings.AimbotSlow = 0.0f;
		Settings.FOV = 80.0f;
		Settings.Crosshair = true;
		Settings.ESP.AimbotFOV = true;
		Settings.ESP.Players = true;
		Settings.WeakSpot = true;
		Settings.ESP.PlayerNames = true;
		Settings.ESP.PlayerWeapons = true;
		Settings.ESP.Box = true;
		Settings.ESP.CornerBox = true;
		Settings.ESP.Shark = false;
		Settings.AimPosSt.head = true;
		Settings.ESP.Distance = true;
		Settings.ESP.Skeleton = true;
		Settings.ESP.UpgradeBench = false;
		Settings.visCheck = true;
		Settings.AimPos = 1;
		Settings.aimkey = VK_RBUTTON;
		Settings.AirStuckKey = VK_SHIFT;
		Settings.BoatTPkey = VK_CONTROL;
		Settings.OverallDistance = 250;
		Settings.ESP.PlayerVisibleColor[0] = 1.0f;
		Settings.ESP.PlayerVisibleColor[1] = 0.0f;
		Settings.ESP.PlayerVisibleColor[2] = 0.0f;
		Settings.ESP.PlayerNotVisibleColor[0] = 1.0f;
		Settings.ESP.PlayerNotVisibleColor[1] = 0.08f;
		Settings.ESP.PlayerNotVisibleColor[2] = 0.6f;
		Settings.ESP.Chests = true;
		Settings.ESP.Boats = false;
		Settings.ESP.Helicopters = false;
		Settings.ESP.Cars = false;
		Settings.ESP.Taxi = false;
		Settings.ESP.Trucks = false;
		Settings.ESP.Llama = true;
		Settings.ESP.SupplyDrop = false;
		Settings.ESP.AgentsBoss = true;
		Settings.ESP.Weapons = true;
		Settings.ESP.Chams = true;
		Settings.ESP.XPCoin = false;
		Settings.ShowInfoBar = false;
		Settings.RadarESP = false;
		Settings.SnaplinePower = 1.0f;
		Settings.ESP.AimLine = true;
		Settings.RadarESPRange = 50000;
		Settings.WarningEnemiesArea = true;
		Settings.ClosestEnemyDistance = true;
		Settings.ESP.MinWeaponTier = 2;
		Settings.BoatBoostMultiplier = 2.f;
		Settings.HelicopterSpeedMultiplier = 2.f;
	}
}