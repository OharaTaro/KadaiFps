#include "DxLib.h"
#include "game.h"

#include "Ball.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// �o�b�N�O���E���h���s��ON��
//	SetAlwaysRunFlag(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	//////////////////////////////////////////
	// ���
	//////////////////////////////////////////

	// �ȉ���ball,ball60,ball30�͂��ꂼ��
	// ball		:�f�B�X�v���C�̃��t���b�V�����[�g�ɍ��킹��update���Ă�ł���
	// ball60	:1�b�Ԃ�60��update()���s����	���Ƃł���Ă��鏈���ɋ߂�
	// ball30	:1�b�Ԃ�60��update()���s����
	// �Ńt���[�����[�g���Ⴄ���̂��^���I�ɓ����ɓ������Ă���
	
	// 3�̃{�[������������������悤Ball�N���X���C������
	// �ǉ��ň����Ȃǂ�v������ꍇ��main()�����C�����Ă悢
	// �C���ł����ꍇ�͉�ʂ̃��t���b�V�����[�g��ύX���Đ������C���ł��Ă��邱�Ƃ��m�F����

	// �������덷�����S�ɂȂ������Ƃ͂ł��Ȃ��̂�
	// �قړ��������ɂȂ��Ă���Ηǂ����̂Ƃ���

	Ball ball{ 0x00ffff };		// ��ʂ̃t���[�����[�g�ɍ��킹�ē���
	Ball ball60{ 0xff00ff };	// 1�b�Ԃ�60��update�����
	Ball ball30{ 0xffff00 };	// 1�b�Ԃ�30��update�����

	LONGLONG  count60 = GetNowHiPerformanceCount();
	LONGLONG  count30 = GetNowHiPerformanceCount();

	while (ProcessMessage() == 0)
	{
	//	LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			ball.init();
			ball60.init();
			ball30.init();
		}
		// �t���[�����[�g�Ɋ֌W�Ȃ����t���[������
		ball.update();
		// 1�b�Ԃ�60�񏈗�
		if (GetNowHiPerformanceCount() - count60 > (1000000 / 60))
		{
			count60 += (1000000 / 60);
			ball60.update();
		}
		
		// 1�b�Ԃ�30�񏈗�
		if (GetNowHiPerformanceCount() - count30 > (1000000 / 30))
		{
			count30 += (1000000 / 30);
			ball30.update();
		}


		ball.draw();
		ball60.draw();
		ball30.draw();


		DrawFormatString(0,0,0xffffff,"FPS:%f", GetFPS());

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

#if false	// FPS���Œ肵�Ȃ�	��ʂ̃��t���b�V�����[�g�Ɉˑ�����
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
#endif
	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}