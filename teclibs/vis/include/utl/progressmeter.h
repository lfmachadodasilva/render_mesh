// Progress Meter
// fabraham@tecgraf.puc-rio.br
#pragma once

#include <utl/lua/progressmeterlua.h>
#ifdef __cplusplus
extern "C" {
#endif

struct ProgressMeter;
struct ProgressMeterPart;

typedef void (*UtlProgressFunction)(float progress, void* funcdata);
typedef void (*UtlSectionProgressFunction)(const char* sectionname, float progress, void* funcdata);

PROGRESSMETERAPI ProgressMeter* utl_pm_create (const char* statsfilename, UtlProgressFunction func, void* funcdata);
PROGRESSMETERAPI void utl_pm_destroy (ProgressMeter* m);
PROGRESSMETERAPI int utl_pm_end (ProgressMeter* m, int abortsave);
PROGRESSMETERAPI int utl_pm_hasprofile (ProgressMeter* m, const char* profile);
PROGRESSMETERAPI void utl_pm_setprofile (ProgressMeter* m, const char* profile);
PROGRESSMETERAPI int utl_pm_update (ProgressMeter* m, const char* section, float v);

PROGRESSMETERAPI ProgressMeterPart* utl_pm_create_part_func (UtlSectionProgressFunction func,
                                                             const char* parentsection,
                                                             void* data,
                                                             const char* partsection,
                                                             int partindex,
                                                             int partcount);
PROGRESSMETERAPI void utl_pm_destroy_part_func (ProgressMeterPart* mp);
PROGRESSMETERAPI void utl_pm_set_part_step (ProgressMeterPart* mp, const char* partsection, int partindex, int partcount);
PROGRESSMETERAPI void utl_pm_update_progress (ProgressMeterPart* mp, float progress);
PROGRESSMETERAPI void utl_pm_update_progress_every (ProgressMeterPart* mp, size_t steps_done, size_t numsteps, size_t freq);
PROGRESSMETERAPI UtlSectionProgressFunction utl_pm_part_get_func (ProgressMeterPart* mp);

#ifdef __cplusplus
}
#endif

