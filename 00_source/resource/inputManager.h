//============================================================
//
//	操作マネージャーヘッダー [inputManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

//************************************************************
//	名前空間宣言
//************************************************************
// 操作空間
namespace input
{
	bool Decide(void);		// 確定操作
	bool Cancel(void);		// キャンセル操作
	bool FieldMenu(void);	// フィールドメニュー操作
}

#endif	// _INPUT_MANAGER_H_
