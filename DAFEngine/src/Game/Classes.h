#pragma once



enum class Blessing {
	Body_Fire,     // Remove Any Immunity
	Body_Water,    // 2s Magic Immunity
	Body_Earth,	   // 2s Melee Immunity
	Body_Air,	   // 2s Ambush Immunity
				   
	Mind_Fire,     // No Heat bar but 10% more damage
	Mind_Water,	   // Non-combat abiblities generate Heat
	Mind_Earth,	   // Heat bar has length of mana bar
	Mind_Air,	   // Instantly convert all Heat points

	Spirit_Fire,   // Increase next ability power by 30%
	Spirit_Water,  // Cast next ability for free
	Spirit_Earth,  // Refill to 100% mana
	Spirit_Air,	   // Cast next ability instantly
};

struct Attack
{
	float Damage;        // Fire - weapon damage
	float Acceleration;	 // Water - weapon balance
	float Impact;		 // Earth - weapon weight
	float Penetration;	 // Air - weapon sharpness
};

struct Block
{
	float Defence;
	float Absorption;
	float Resilience;
	float Thickness;
};


enum class Sect
{
	// W a r r i o r
	Body_Fire_Damage,   // Red Warrior
	Body_Fire_Defence,  // Paladin Order
	Body_Fire_Crafting,	// Blacksmithing
	Body_Fire_Evil,		// 
	Body_Fire_Holy,		// Order

	Body_Water_Damage,  // Blue Warrior
	Body_Water_Defence,	//
	Body_Water_Crafting,//
	Body_Water_Evil,	//
	Body_Water_Holy,	//

	Body_Earth_Damage,  // Green Warrior
	Body_Earth_Defence,	//
	Body_Earth_Crafting,//
	Body_Earth_Evil,	//
	Body_Earth_Holy,	//

	Body_Air_Damage,    // Grey Warrior
	Body_Air_Defence,	//
	Body_Air_Crafting,	//
	Body_Air_Evil,		//
	Body_Air_Holy,		//

	// R o g u e
	Mind_Fire_Damage,
	Mind_Fire_Defence,
	Mind_Fire_Crafting,
	Mind_Fire_Evil,
	Mind_Fire_Holy,

	Mind_Water_Damage,
	Mind_Water_Defence,
	Mind_Water_Crafting,
	Mind_Water_Evil,
	Mind_Water_Holy,

	Mind_Earth_Damage,
	Mind_Earth_Defence,
	Mind_Earth_Crafting,
	Mind_Earth_Evil,
	Mind_Earth_Holy,
	
	Mind_Air_Damage,
	Mind_Air_Defence,
	Mind_Air_Crafting,
	Mind_Air_Evil,
	Mind_Air_Holy,

	// M a g e
	Spirit_Fire_Damage,
	Spirit_Fire_Defence,
	Spirit_Fire_Crafting,
	Spirit_Fire_Evil,
	Spirit_Fire_Holy,
	
	Spirit_Water_Damage,
	Spirit_Water_Defence,
	Spirit_Water_Crafting,
	Spirit_Water_Evil,
	Spirit_Water_Holy,
	
	Spirit_Earth_Damage,
	Spirit_Earth_Defence,
	Spirit_Earth_Crafting,
	Spirit_Earth_Evil,
	Spirit_Earth_Holy,

	Spirit_Air_Damage,
	Spirit_Air_Defence,
	Spirit_Air_Crafting,
	Spirit_Air_Evil,
	Spirit_Air_Holy,
};