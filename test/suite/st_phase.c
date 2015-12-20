
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <sophia.h>
#include <libss.h>
#include <libsf.h>
#include <libsr.h>
#include <libsv.h>
#include <libso.h>
#include <libst.h>

void st_phase_commit(void)
{
	void *env = st_r.env;

	switch (st_r.phase_compaction_scene) {
	case 0: break;
	case 1:
		t( sp_setint(env, "db.test.branch", 0) == 0 );
		break;
	case 2:
		t( sp_setint(env, "db.test.branch", 0) == 0 );
		t( sp_setint(env, "db.test.compact", 0) == 0 );
		break;
	case 3:
		t( sp_setint(env, "log.rotate", 0) == 0 );
		t( sp_setint(env, "log.gc", 0) == 0 );
		break;
	case 4:
		if (st_r.phase_compaction == 0) {
			t( sp_setint(env, "db.test.branch", 0) == 0 );
			t( sp_setint(env, "log.rotate", 0) == 0 );
			t( sp_setint(env, "log.gc", 0) == 0 );
			st_r.phase_compaction = 1;
		} else
		if (st_r.phase_compaction == 1) {
			t( sp_setint(env, "db.test.compact", 0) == 0 );
			st_r.phase_compaction = 0;
		}
		break;
	default: t(0);
	}
}
