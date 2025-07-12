#include "modding.h"
#include "global.h"
#include "gCJSkel.h"
#include "cj_lefthand_closed.h"
#include "cj_ocarina.h"
#include "cj_bow.h"
#include "cj_hookshot.h"
#include "gBigSmokeSkel.h"
#include "ultra64.h"
#include "eztr_api.h"
#include "anims/gCJSkel_ocarinaGcj_ocarina_startAnim.h"
#include "anims/gCJSkel_ocarinaGcj_ocarina_swingAnim.h"
#include "playermodelmanager_api.h"

extern PlayerAgeProperties sPlayerAgeProperties[];
extern LinkAnimationHeader gPlayerAnim_link_normal_okarina_start[];
extern LinkAnimationHeader gPlayerAnim_link_normal_okarina_swing[];
extern Input *sPlayerControlInput;

extern Gfx gCJSkel_handsclosed_bone015_gLinkHumanLeftHandLimb_mesh_layer_Opaque_tri_0[];
extern Gfx gCJSkel_handsclosed_bone018_gLinkHumanRightHandLimb_mesh_layer_Opaque_tri_0[];

static Mtx sCjMaskMtx;

PLAYERMODELMANAGER_CALLBACK_REGISTER_MODELS
void registerCjModels() {

    PlayerModelManagerHandle h = PLAYERMODELMANAGER_REGISTER_MODEL("playas_cj", PMM_MODEL_TYPE_ADULT);

    PlayerModelManager_setDisplayName(h, "CJ");

    PlayerModelManager_setAuthor(h, "Reonu");

    PlayerModelManager_setSkeleton(h, &gCJSkel);

    PlayerModelManager_setDisplayList(h, PMM_DL_RFIST, gCJSkel_handsclosed_bone018_gLinkHumanRightHandLimb_mesh_layer_Opaque_tri_0);
    PlayerModelManager_setDisplayList(h, PMM_DL_LFIST, gCJSkel_handsclosed_bone015_gLinkHumanLeftHandLimb_mesh_layer_Opaque_tri_0);
    PlayerModelManager_setDisplayList(h, PMM_DL_LHAND_BOTTLE, gCJSkel_bone015_gLinkHumanLeftHandLimb_mesh_layer_Opaque);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_LFOREARM, gCJSkel_bone014_gLinkHumanLeftForearmLimb_mesh_layer_Opaque);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_LHAND, gCJSkel_handsclosed_bone015_gLinkHumanLeftHandLimb_mesh_layer_Opaque_tri_0);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_RHAND, gCJSkel_handsclosed_bone018_gLinkHumanRightHandLimb_mesh_layer_Opaque_tri_0);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_RFOREARM, gCJSkel_bone017_gLinkHumanRightForearmLimb_mesh_layer_Opaque);

    guPosition(&sCjMaskMtx, 0.0f, 0.0f, 0.0f, 0.5f, 350.0f, - 10.0f, 0.0f);
    PlayerModelManager_setMatrix(h, PMM_MTX_MASKS, &sCjMaskMtx);

    //PlayerModelManager_setLoadCallback(h, onCjLoad, NULL);
    //PlayerModelManager_setUnloadCallback(h, onCjUnload, NULL);
}
