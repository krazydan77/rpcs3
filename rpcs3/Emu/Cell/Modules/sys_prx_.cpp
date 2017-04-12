#include "stdafx.h"
#include "Emu/System.h"
#include "Emu/Cell/PPUModule.h"

#include "Emu/Cell/lv2/sys_prx.h"
#include "sysPrxForUser.h"

extern logs::channel sysPrxForUser;

s32 sys_prx_load_module()
{
	sysPrxForUser.todo("sys_prx_load_module()");
	return CELL_OK;
}

s32 sys_prx_load_module_by_fd()
{
	sysPrxForUser.todo("sys_prx_load_module_by_fd()");
	return CELL_OK;
}

s32 sys_prx_load_module_on_memcontainer()
{
	sysPrxForUser.todo("sys_prx_load_module_on_memcontainer()");
	return CELL_OK;
}

s32 sys_prx_load_module_on_memcontainer_by_fd()
{
	sysPrxForUser.todo("sys_prx_load_module_on_memcontainer_by_fd()");
	return CELL_OK;
}

s32 sys_prx_load_module_list()
{
	sysPrxForUser.todo("sys_prx_load_module_list()");
	return CELL_OK;
}

s32 sys_prx_load_module_list_on_memcontainer()
{
	sysPrxForUser.todo("sys_prx_load_module_list_on_memcontainer()");
	return CELL_OK;
}

s32 sys_prx_start_module()
{
	sysPrxForUser.todo("sys_prx_start_module()");
	return CELL_OK;
}

s32 sys_prx_stop_module()
{
	sysPrxForUser.todo("sys_prx_stop_module()");
	return CELL_OK;
}

s32 sys_prx_unload_module()
{
	sysPrxForUser.todo("sys_prx_unload_module()");
	return CELL_OK;
}

s32 sys_prx_register_library()
{
	sysPrxForUser.todo("sys_prx_register_library()");
	return CELL_OK;
}

s32 sys_prx_unregister_library()
{
	sysPrxForUser.todo("sys_prx_unregister_library()");
	return CELL_OK;
}

s32 sys_prx_get_module_list()
{
	sysPrxForUser.todo("sys_prx_get_module_list()");
	return CELL_OK;
}

error_code sys_prx_get_module_info(u32 id, u64 flags, vm::ptr<sys_prx_module_info_t> info)
{
	sysPrxForUser.trace("sys_prx_get_module_info(id=0x%x, flags=0x%x, info=*0x%x)", id, flags, info);

	if (!info)
	{
		return CELL_EINVAL;
	}

	vm::var<sys_prx_module_info_option_t> opt;
	opt->size = opt.size();
	opt->info = info;

	// Call the syscall
	return _sys_prx_get_module_info(id, 0, opt);
}

error_code sys_prx_get_module_id_by_name(vm::cptr<char> name, u64 flags, vm::ps3::ptr<sys_prx_get_module_id_by_name_option_t> pOpt)
{
	sysPrxForUser.trace("sys_prx_get_module_id_by_name(name=%s, flags=0x%x, pOpt=*0x%x)", name, flags, pOpt);

	if (flags || pOpt)
	{
		return CELL_EINVAL;
	}

	// Call the syscall
	return _sys_prx_get_module_id_by_name(name, u64{0}, vm::null);
}

error_code sys_prx_get_module_id_by_address(u32 addr)
{
	sysPrxForUser.trace("sys_prx_get_module_id_by_address()");

	// Call the syscall
	return _sys_prx_get_module_id_by_address(addr);
}

s32 sys_prx_exitspawn_with_level()
{
	sysPrxForUser.fatal("sys_prx_exitspawn_with_level()");
	return CELL_OK;
}

error_code sys_prx_get_my_module_id(ppu_thread& ppu, ppu_thread& _do, ppu_thread& _not, ppu_thread& _call)
{
	sysPrxForUser.trace("sys_prx_get_my_module_id()");

	// Call the syscall using the LR
	return _sys_prx_get_module_id_by_address(ppu.lr);
}

void sysPrxForUser_sys_prx_init()
{
	REG_FUNC(sysPrxForUser, sys_prx_load_module);
	REG_FUNC(sysPrxForUser, sys_prx_load_module_by_fd);
	REG_FUNC(sysPrxForUser, sys_prx_load_module_on_memcontainer);
	REG_FUNC(sysPrxForUser, sys_prx_load_module_on_memcontainer_by_fd);
	REG_FUNC(sysPrxForUser, sys_prx_load_module_list);
	REG_FUNC(sysPrxForUser, sys_prx_load_module_list_on_memcontainer);
	REG_FUNC(sysPrxForUser, sys_prx_start_module);
	REG_FUNC(sysPrxForUser, sys_prx_stop_module);
	REG_FUNC(sysPrxForUser, sys_prx_unload_module);
	REG_FUNC(sysPrxForUser, sys_prx_register_library);
	REG_FUNC(sysPrxForUser, sys_prx_unregister_library);
	REG_FUNC(sysPrxForUser, sys_prx_get_module_list);
	REG_FUNC(sysPrxForUser, sys_prx_get_module_info);
	REG_FUNC(sysPrxForUser, sys_prx_get_module_id_by_name);
	REG_FUNC(sysPrxForUser, sys_prx_get_module_id_by_address);
	REG_FUNC(sysPrxForUser, sys_prx_exitspawn_with_level);
	REG_FUNC(sysPrxForUser, sys_prx_get_my_module_id);
}
