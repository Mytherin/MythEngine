

#pragma once


namespace myth
{
	namespace io
	{
		typedef unsigned int obj_id;
		typedef unsigned char type_id;

		const type_id type_error = 0;
		const type_id type_shader = 1;
		const type_id type_texture = 2;
		const type_id type_mesh = 3;
		const type_id type_boundingvolume = 4;

	}
}