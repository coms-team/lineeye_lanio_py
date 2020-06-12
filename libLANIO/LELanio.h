//***************************************************************************
//* LANIOライブラリ ヘッダファイル
//***************************************************************************

#ifdef _WINDOWS
#ifdef EXPORT_DECLSPEC
#define DECLSPEC extern "C" __declspec(dllexport) int __stdcall
#else
#define DECLSPEC extern "C" __declspec(dllimport) int __stdcall
#endif
#else
#define DECLSPEC int
typedef int BOOL;
#endif

//***************************************************************************
//* 型定義、定数定義
//***************************************************************************

//***************************************************************************
//* LANIOハンドラ
//***************************************************************************
#define hLANIO int

//***************************************************************************
//* LELanioGetLastErrorが返すエラーコード
//***************************************************************************
enum LANIOERROR {
	LELANIOERR_NOINIT = 1,			//* 初期化されていません。LELanioInitを実行してください。
	LELANIOERR_NOLANIO,				//* 検索した結果、LANIOが発見できませんでした。
	LELANIOERR_NOTEXIST,			//* 検索で発見したLANIOより多い値を指定しました。
	LELANIOERR_NOTFOUND,			//* 指定された条件のLANIOを発見できませんでした。
	LELANIOERR_NOCONNECTED,			//* LANIOと接続していません。LELanioConnectを実行してください。
	LELANIOERR_INVALIDOPERATION,	//* 指定された操作は実行できません。
	LELANIOERR_ALREADY_CONNECTED,	//* すでに接続しています。
	LELANIOERR_OVERCONNECTMAX,		//* 接続最大数を超過しました。
	LELANIOERR_INVALIDRETURNVALUE,	//* 不正な戻り値が返りました。
};

//***************************************************************************
//* LELanioGetModelで取得するLANIOモデル
//***************************************************************************
enum LANIOMODEL {
	LA2R3PP = 0,
	LA3R2P  = 1,		// LA-3R2P-P含む
	LA7P    = 2,		// LA-7P-P / LA-7P-A含む
	LA5R    = 3,
	LA5T2S  = 4,		// LA-5T2S-P含む
	LA5PP   = 5,
	LA3R3PP = 6,
	LA232R  = 7,
	LA232T  = 8,
	LA485R  = 9,
	LA485T  = 10,
	NO_GETMODEL = -1,
};

//***************************************************************************
//* 初期化、終了、エラー取得関数
//***************************************************************************

//***************************************************************************
//*		LANIOライブラリを初期化します。
//***************************************************************************
DECLSPEC LELanioInit();

//***************************************************************************
//*		LANIOライブラリの使用を終了します。
//***************************************************************************
DECLSPEC LELanioEnd();

//***************************************************************************
//*		直前に発生したエラー番号を取得します。
//*		戻り値 : エラーの情報を返します
//***************************************************************************
DECLSPEC LELanioGetLastError();

//***************************************************************************
//* LANIO検索関数
//***************************************************************************

//***************************************************************************
//*		自動的にLANIOのIDとModelを取得する機能についての設定をします。
//*		引数   : enable  この機能を使用する場合はTRUE(1)、しない場合はFALSE(0)
//*		         port    IDとModelを自動取得するシリアルのポート番号
//***************************************************************************
DECLSPEC LELanioSetAutoRequestIdModel(BOOL enable, int port);

//***************************************************************************
//*		LAN内にあるLANIOを検索します。
//*		引数   : msec    タイムアウト時間（単位 m秒）
//*		戻り値 : 発見したLANIOの数。発見できなかった場合は0。エラー時は-1
//***************************************************************************
DECLSPEC LELanioSearch(int msec);

//***************************************************************************
//* LANIO情報取得関数
//***************************************************************************

//***************************************************************************
//*		検索したLANIOのIPアドレスを取得します。
//*		引数   : lanio       LANIO番号
//*		         ipaddress   IPアドレスを取得するバッファへのポインタ(16byte必要)
//***************************************************************************
DECLSPEC LELanioGetIpAddress(int lanio, char *ipaddress);

//***************************************************************************
//*		検索したLANIOのMACアドレスを取得します。
//*		引数   : lanio       LANIO番号
//*		         macaddress  MACアドレスを取得するバッファへのポインタ(6byte必要)
//***************************************************************************
DECLSPEC LELanioGetMacAddress(int lanio, unsigned char *macaddress);

//***************************************************************************
//*		LANIOのID番号を取得します。
//*		引数   : lanio   LANIO番号
//*		         id      LANIOのIDを取得するバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioGetId(int lanio, int *id);

//***************************************************************************
//*		LANIOのモデルを取得します。
//*		引数   : lanio   LANIO番号
//*		         model   LANIOのモデルを取得するバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioGetModel(int lanio, int *model);

//***************************************************************************
//*		検索したLANIOに対してIDとモデル番号を質問します。
//*		引数   : lanio   LANIO番号
//*		         id      LANIOのIDを取得するバッファへのポインタ
//*		         model   LANIOのモデルを取得するバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioRequestIdModel(int lanio, int *id, int *model);

//***************************************************************************
//* LANIO接続関数
//***************************************************************************

//***************************************************************************
//*		LELanioSearchによって発見された順番を指定して接続します。
//*		引数   : lanio   LANIO番号
//*		戻り値 : エラー時は-1、正常終了時はLANIO操作ハンドルを返します
//***************************************************************************
DECLSPEC LELanioConnect(int lanio);

//***************************************************************************
//*		IDとモデルを指定して接続します。
//*		引数   : id      LANIOのID番号
//*		         model   LANIOのモデル
//*		戻り値 : エラー時は-1、正常終了時はLANIO操作ハンドルを返します
//***************************************************************************
DECLSPEC LELanioConnectByIdModel(int id, int model);

//***************************************************************************
//*		IPアドレスを指定して接続します。
//*		引数   : ipaddress   IPアドレス文字列バッファへのポインタ
//*		戻り値 : エラー時は-1、正常終了時はLANIO操作ハンドルを返します
//***************************************************************************
DECLSPEC LELanioConnectByIpAddress(char *ipaddress);

//***************************************************************************
//*		MACアドレスを指定して接続します。
//*		引数   : macaddress  MACアドレスバッファへのポインタ
//*		戻り値 : エラー時は-1、正常終了時はLANIO操作ハンドルを返します
//***************************************************************************
DECLSPEC LELanioConnectByMacAddress(unsigned char *macaddress);

//***************************************************************************
//*		IPアドレスもしくはURLを指定して接続します。
//*		引数   : address IPアドレスまたはurl文字列バッファへのポインタ
//*		         msec    タイムアウト時間（単位 m秒）
//*		戻り値 : エラー時は-1、正常終了時はLANIO操作ハンドルを返します
//***************************************************************************
DECLSPEC LELanioConnectDirect(char *address, int msec);

//***************************************************************************
//* LANIO切断関数
//***************************************************************************

//***************************************************************************
DECLSPEC LELanioClose(hLANIO handle);
//*		LANIOとの接続を切断します。
//*		引数   : handle  LANIO操作ハンドル
//***************************************************************************

//***************************************************************************
//* 入出力関数
//***************************************************************************

//***************************************************************************
//*		LANIOのDOを操作します。一点単位の操作に使用します。
//*		引数   : handle  LANIO操作ハンドル
//*		         pio     操作するDOポート番号。DO1=0、DO2=1...
//*		         active  ONなら1、OFFなら0
//***************************************************************************
DECLSPEC LELanioOutPio(hLANIO handle, int pio, BOOL active);

//***************************************************************************
//*		LANIOのDOを操作します。全てのDOに対し一斉に操作する時に使用します。
//*		引数   : handle  LANIO操作ハンドル
//*		         piobit  DOポートの設定。最下位ビットからDO1、DO2...に対応します
//***************************************************************************
DECLSPEC LELanioOutPioAll(hLANIO handle, int piobit);

//***************************************************************************
//*		LANIOのDIを取得します。一点単位の取得に使用します。
//*		引数   : handle  LANIO操作ハンドル
//*		         pio     取得するDIポート番号。DI1=0、DI2=1...に対応します
//*		         active  ONなら1、OFFなら0が入るバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioInPio(hLANIO handle, int pio, BOOL *active);

//***************************************************************************
//*		LANIOのDIを取得します。全てのDIに対し一斉に取得する時に使用します。
//*		引数   : handle  LANIO操作ハンドル
//*		         piobit  DIポートの内容が入るバッファへのポインタ
//*		                 最下位ビットからDI1、DI2...
//***************************************************************************
DECLSPEC LELanioInPioAll(hLANIO handle, int *piobit);

//***************************************************************************
//*		LANIOの現在のDO状態を取得します。一点単位の取得に使用します。
//*		引数   : handle  LANIO操作ハンドル
//*		         pio     取得するDOポート番号。DO1=0、DO2=1...に対応します
//*		         active  ONなら1、OFFなら0が入るバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioGetOut(hLANIO handle, int pio, BOOL *active);

//***************************************************************************
//*		LANIOの現在のDO状態を取得します。全てのDOに対し一斉に取得する時に使用します。
//*		引数   : handle  LANIO操作ハンドル
//*		         piobit  DOポートの内容が入るバッファへのポインタ
//*		                 最下位ビットからDO1、DO2...
//***************************************************************************
DECLSPEC LELanioGetOutAll(hLANIO handle, int *piobit);

//***************************************************************************
//*		LANIOの出力端子自動ON/OFFの開始/停止を行います
//*		引数   : handle  LANIO操作ハンドル
//*		         active  自動ON/OFFを開始する=0以外、停止する=0
//***************************************************************************
DECLSPEC LELanioSetAutoSwitchingActive(hLANIO handle, BOOL active);

//***************************************************************************
//*		LANIOの出力端子自動ON/OFFの開始/停止設定を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         active  自動ON/OFF状態が入るバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioGetAutoSwitchingActive(hLANIO handle, BOOL *active);

//***************************************************************************
//*		LANIOの出力端子自動ON/OFFの周期を設定します
//*		引数   : handle  LANIO操作ハンドル
//*		         msec    周期（単位 m秒）
//***************************************************************************
DECLSPEC LELanioSetAutoSwitchingTime(hLANIO handle, int msec);

//***************************************************************************
//*		LANIOの出力端子自動ON/OFFの周期設定を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         msec    周期（単位 m秒）が入るバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioGetAutoSwitchingTime(hLANIO handle, int *msec);

//***************************************************************************
//*		LANIOの出力端子自動ON/OFFを行うDOを設定します。
//*		引数   : handle  LANIO操作ハンドル
//*		         autoswdo 最下位ビットより、DO1～DO5で自動ON/OFFを行う端子が1
//***************************************************************************
DECLSPEC LELanioSetAutoSwitchingPio(hLANIO handle, int autoswdo);

//***************************************************************************
//*		LANIOの出力端子自動ON/OFFを行うDO設定を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         autoswdo 自動ON/OFF実行DO設定を取得するバッファへのポインタ
//***************************************************************************
DECLSPEC LELanioGetAutoSwitchingPio(hLANIO handle, int *autoswdo);

//***************************************************************************
//*		LANIOの無通信状態になった後の接続維持時間を設定する
//*		引数   : handle  LANIO操作ハンドル
//*		         time    時間
//*		                 0x00:すぐ切断 0x04: 3sec  0x08:50sec  0x0c:10min
//*		                 0x01:300ms    0x05: 5sec  0x09: 1min  0x0d:30min
//*		                 0x02:500ms    0x06:10sec  0x0a: 3min  0x0e:50min
//*		                 0x03: 1sec    0x07:30sec  0x0b: 5min  0x0f:無制限
//***************************************************************************
DECLSPEC LELanioSetDisconnectionTime(hLANIO handle, int time);

//***************************************************************************
//*		LANIOの無通信状態になった後の接続維持時間を取得する
//*		引数   : handle  LANIO操作ハンドル
//*		         time    時間を取得するバッファへのポインタ
//*		                 0x00:すぐ切断 0x04: 3sec  0x08:50sec  0x0c:10min
//*		                 0x01:300ms    0x05: 5sec  0x09: 1min  0x0d:30min
//*		                 0x02:500ms    0x06:10sec  0x0a: 3min  0x0e:50min
//*		                 0x03: 1sec    0x07:30sec  0x0b: 5min  0x0f:無制限
//***************************************************************************
DECLSPEC LELanioGetDisconnectionTime(hLANIO handle, int *time);

//***************************************************************************
//*		LANIOの定期通知時間を設定する
//*		引数   : handle  LANIO操作ハンドル
//*		                 0x00:通知なし 0x04: 3min     0x08:設定禁止  0x0c:設定禁止
//*		                 0x01:10sec    0x05:設定禁止  0x09:設定禁止  0x0d:設定禁止
//*		                 0x02:30sec    0x06:設定禁止  0x0a:設定禁止  0x0e:設定禁止
//*		                 0x03:60sec    0x07:設定禁止  0x0b:設定禁止  0x0f:設定禁止
//***************************************************************************
DECLSPEC LELanioSetNoticeTime(hLANIO handle, int time);

//***************************************************************************
//*		LANIOの定期通知時間を取得する
//*		引数   : handle  LANIO操作ハンドル
//*		                 0x00:通知なし 0x04: 3min   0x08:  ---   0x0c:  ---
//*		                 0x01:10sec    0x05:  ---   0x09:  ---   0x0d:  ---
//*		                 0x02:30sec    0x06:  ---   0x0a:  ---   0x0e:  ---
//*		                 0x03:60sec    0x07:  ---   0x0b:  ---   0x0f:  ---
//***************************************************************************
DECLSPEC LELanioGetNoticeTime(hLANIO handle, int *time);

//***************************************************************************
//*		LANIOのチャタリング判定の基準時間を設定する
//*		引数   : handle  LANIO操作ハンドル
//*		         time    時間(ms単位 4ms～20ms）
//***************************************************************************
DECLSPEC LELanioSetDiDetectTime(hLANIO handle, int time);

//***************************************************************************
//*		LANIOのチャタリング判定の基準時間を取得する
//*		引数   : handle  LANIO操作ハンドル
//*		         time    時間を取得するバッファへのポインタ(ms単位 4ms～20ms）
//***************************************************************************
DECLSPEC LELanioGetDiDetectTime(hLANIO handle, int *time);

//***************************************************************************
//*		LANIOのメールアラートを実行する入力端子を設定します
//*		引数   : handle  LANIO操作ハンドル
//*		         enable  メールアラートを実行するビットを1で指定
//*		                 最下位ビットからDI1、DI2...
//***************************************************************************
DECLSPEC LELanioSetDiMailEnable(hLANIO handle, int enable);

//***************************************************************************
//*		LANIOのメールアラートを実行する入力端子を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         enable  メールアラートを実行するビットを1で指定
//*		                 最下位ビットからDI1、DI2...
//***************************************************************************
DECLSPEC LELanioGetDiMailEnable(hLANIO handle, int *enable);

//***************************************************************************
//*		LANIOのメールアラートを実行する論理状態を設定します
//*		引数   : handle  LANIO操作ハンドル
//*		         logic   立ち上がりエッジでメールアラートを実行するビットを1で指定
//*		                 最下位ビットからDI1、DI2...
//***************************************************************************
DECLSPEC LELanioSetDiMailLogic(hLANIO handle, int logic);

//***************************************************************************
//*		LANIOのメールアラートを実行する論理状態を設定します
//*		引数   : handle  LANIO操作ハンドル
//*		         logic   立ち上がりエッジでメールアラートを実行するビットを1で指定
//*		                 最下位ビットからDI1、DI2...
//***************************************************************************
DECLSPEC LELanioGetDiMailLogic(hLANIO handle, int *logic);

//***************************************************************************
//*		PulseModeに入ります
//*		引数   : handle  LANIO操作ハンドル
//***************************************************************************
DECLSPEC LELanioPulseModeOn(hLANIO handle);

//***************************************************************************
//*		PulseModeを終了します
//*		引数   : handle  LANIO操作ハンドル
//***************************************************************************
DECLSPEC LELanioPulseModeOff(hLANIO handle);

//***************************************************************************
//*		PulseMode状態を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         mode    PulseMode状態。モード中なら1、モード中でなければ0
//***************************************************************************
DECLSPEC LELanioPulseModeGetState(hLANIO handle, int *mode);

//***************************************************************************
//*		PulseModeのパルス数を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         value   パルス数。オーバーフロー状態の場合-1
//***************************************************************************
DECLSPEC LELanioPulseModeGetCount(hLANIO handle, int *value);

//***************************************************************************
//*		PulseModeの設定をします
//*		引数   : handle  LANIO操作ハンドル
//*		         pio     操作するDIポート番号。DI1=0、DI2=1...
//*		         edge    0で立ち上がり、1で立ち下がりエッジ
//*		         time    測定時間
//*		                 0:START-STOP  1:100msec  2:1sec  3:10sec
//*		         chatter チャタリング抑制
//*		                 0:なし  1～3:設定不可  4～20:4～20msec
//***************************************************************************
DECLSPEC LELanioPulseModeSetConfig(hLANIO handle, int pio, BOOL edge, int time, int chatter);

//***************************************************************************
//*		PulseModeの設定を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         pio     操作するDIポート番号。DI1=0、DI2=1...
//*		         edge    0で立ち上がり、1で立ち下がりエッジ
//*		         time    測定時間
//*		                 0:START-STOP  1:100msec  2:1sec  3:10sec
//*		         chatter チャタリング抑制
//*		                 0:なし  1～3:設定不可  4～20:4～20msec
//***************************************************************************
DECLSPEC LELanioPulseModeGetConfig(hLANIO handle, int *pio, BOOL *edge, int *time, int *chatter);

//***************************************************************************
//*		パルス連続測定を開始します
//*		引数   : handle  LANIO操作ハンドル
//***************************************************************************
DECLSPEC LELanioPulseModeContinuesOn(hLANIO handle);

//***************************************************************************
//*		パルス連続測定を終了します
//*		引数   : handle  LANIO操作ハンドル
//***************************************************************************
DECLSPEC LELanioPulseModeContinuesOff(hLANIO handle);

//***************************************************************************
//*		パルス連続測定状態を取得します
//*		引数   : handle  LANIO操作ハンドル
//*		         mode    パルス連続測定状態中なら1、でなければ0
//***************************************************************************
DECLSPEC LELanioPulseModeContinuesGetState(hLANIO handle, int *mode);
