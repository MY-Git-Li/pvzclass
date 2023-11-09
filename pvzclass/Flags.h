﻿namespace PVZ
{
#pragma region DamageRangeFlags

	//判定僵尸是否符合指定条件的标志位，以 DAMAGERF 开头。
	typedef int DamageRangeFlags;

	//是否位于地面上（或水面上）。
	const DamageRangeFlags DAMAGERF_GROUND = (1 << 0);
	//是否飞行。
	const DamageRangeFlags DAMAGERF_FLYING = (1 << 1);
	//是否潜水。
	const DamageRangeFlags DAMAGERF_SUBMERGED = (1 << 2);
	//Deprecated
	const DamageRangeFlags DAMAGERF_DOG = (1 << 3);
	//是否正在落地（或出土）。
	const DamageRangeFlags DAMAGERF_OFF_GROUND = (1 << 4);
	//是否考虑已被击杀的僵尸。
	const DamageRangeFlags DAMAGERF_DYING = (1 << 5);
	//是否位于地下。
	const DamageRangeFlags DAMAGERF_UNDERGROUND = (1 << 6);
	//是否被魅惑。
	const DamageRangeFlags DAMAGERF_HYPNOTIZED = (1 << 7);

	//全体未被魅惑的僵尸。
	const DamageRangeFlags DAMAGERF_ALL = DAMAGERF_GROUND | DAMAGERF_FLYING
		| DAMAGERF_SUBMERGED | DAMAGERF_DOG | DAMAGERF_OFF_GROUND | DAMAGERF_DYING | DAMAGERF_UNDERGROUND;
	//全体被魅惑的僵尸。
	const DamageRangeFlags DAMAGERF_ALL_HYPNOTIZED = DAMAGERF_HYPNOTIZED | DAMAGERF_ALL;

#pragma endregion

#pragma region DamageFlags
	
	//判定对僵尸伤害是否具有某种特效的标志位，以 DAMAGEF 开头。
	typedef int DamageFlags;

	//无特效。
	const DamageFlags DAMAGEF_NONE = 0;
	//无视II类护甲。
	const DamageFlags DAMAGEF_SIDE = (1 << 0);
	//穿透II类护甲。
	const DamageFlags DAMAGEF_SPUTTER = (1 << 1);
	//有减速效果。
	const DamageFlags DAMAGEF_FREEZE = (1 << 2);
	//不导致僵尸闪烁。
	const DamageFlags DAMAGEF_NOFLASH = (1 << 3);
	//不显示击杀粒子效果。
	const DamageFlags DAMAGEF_NOLEAVEBODY = (1 << 4);
	//地刺类伤害。
	const DamageFlags DAMAGEF_SPIKE = (1 << 5);
#pragma endregion
}