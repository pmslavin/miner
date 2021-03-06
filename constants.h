#ifndef _MINER_CONSTANTS_H_
#define _MINER_CONSTANTS_H_

namespace Colours{

	const uint32_t Black		= 0x00000000;
	const uint32_t Yellow		= 0x00FFFF00;
	const uint32_t Iron		= 0x00E04714;
	const uint32_t Copper		= 0x000EAD88;
	const uint32_t Gold		= 0x00F0D000;
	const uint32_t Uranium		= 0x0000FF00;
	unsigned const char Uranium_Dark_byte = 0xA7;


	namespace Cell{

		namespace Empty{
			const uint32_t Light = 0x00825A00;
			const uint32_t Dark = 0x005C4000;
		};
		namespace Drilled{
			const uint32_t Light = 0x00818582;
			const uint32_t Dark  = 0x006A6A6A;
		};
	};

	namespace Surface{
		const uint32_t Sky	= 0x00528EFF;
		const uint32_t Grass	= 0x0029E639;
		const uint32_t Soil	= 0x005C1C00;
		const uint32_t Shaft	= 0x00606060;
	};
};


#endif
