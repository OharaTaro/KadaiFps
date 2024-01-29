#include "DxLib.h"
#include "game.h"

#include "Ball.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// バックグラウンド実行をONに
//	SetAlwaysRunFlag(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	//////////////////////////////////////////
	// 問題
	//////////////////////////////////////////

	// 以下のball,ball60,ball30はそれぞれ
	// ball		:ディスプレイのリフレッシュレートに合わせてupdateを呼んでいる
	// ball60	:1秒間に60回update()が行われる	授業でやっている処理に近い
	// ball30	:1秒間に60回update()が行われる
	// でフレームレートが違う物体を疑似的に同時に動かしている
	
	// 3つのボールが同じ動きをするようBallクラスを修正せよ
	// 追加で引数などを要求する場合はmain()側も修正してよい
	// 修正できた場合は画面のリフレッシュレートを変更して正しく修正できていることを確認せよ

	// ただし誤差を完全になくすことはできないので
	// ほぼ同じ動きになっていれば良いものとする

	Ball ball{ 0x00ffff };		// 画面のフレームレートに合わせて動く
	Ball ball60{ 0xff00ff };	// 1秒間に60回updateされる
	Ball ball30{ 0xffff00 };	// 1秒間に30回updateされる

	LONGLONG  count60 = GetNowHiPerformanceCount();
	LONGLONG  count30 = GetNowHiPerformanceCount();

	while (ProcessMessage() == 0)
	{
	//	LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			ball.init();
			ball60.init();
			ball30.init();
		}
		// フレームレートに関係なく毎フレーム処理
		ball.update();
		// 1秒間に60回処理
		if (GetNowHiPerformanceCount() - count60 > (1000000 / 60))
		{
			count60 += (1000000 / 60);
			ball60.update();
		}
		
		// 1秒間に30回処理
		if (GetNowHiPerformanceCount() - count30 > (1000000 / 30))
		{
			count30 += (1000000 / 30);
			ball30.update();
		}


		ball.draw();
		ball60.draw();
		ball30.draw();


		DrawFormatString(0,0,0xffffff,"FPS:%f", GetFPS());

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

#if false	// FPSを固定しない	画面のリフレッシュレートに依存する
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
#endif
	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}