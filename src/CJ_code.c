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

bool gIsCjLoaded = false;

extern s16 gPlayerAnim_link_normal_okarina_start_Data[];
extern s16 gPlayerAnim_link_normal_okarina_swing_Data[];

LinkAnimationHeader gVanillaPlayerAnim_link_normal_okarina_start = {
    {12}, gPlayerAnim_link_normal_okarina_start_Data};

LinkAnimationHeader gVanillaPlayerAnim_link_normal_okarina_swing = {
    {68}, gPlayerAnim_link_normal_okarina_swing_Data};

void onCjLoad(void *userdata) {
    gIsCjLoaded = true;
}

void onCjUnload(void *userdata) {
    gIsCjLoaded = false;
}

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

    //PlayerModelManager_setLoadCallback(h, onCjLoad, NULL);
    //PlayerModelManager_setUnloadCallback(h, onCjUnload, NULL);
}

bool isVanillaOcarinaSaved = false;
bool isCjAnims = false;

void updateLink(PlayState* play) {
    if (!gIsCjLoaded) {
        *(LinkAnimationHeader *)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_start) = gVanillaPlayerAnim_link_normal_okarina_start;
        *(LinkAnimationHeader *)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_swing) = gVanillaPlayerAnim_link_normal_okarina_swing;
        return;
    }

    PlayerAgeProperties CJProperties;
    Player* player = GET_PLAYER(play);
    if (player->transformation == PLAYER_FORM_HUMAN) {
        CJProperties = sPlayerAgeProperties[PLAYER_FORM_ZORA];
        CJProperties.unk_28 = 44.8f;
        CJProperties.unk_3C = 15.0f;
        CJProperties.unk_44 = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_44;
        CJProperties.unk_4A->x = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_4A->x;
        CJProperties.unk_4A->y = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_4A->y;
        CJProperties.unk_4A->z = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_4A->z;
        CJProperties.unk_62->x = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_62->x;
        CJProperties.unk_62->y = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_62->y;
        CJProperties.unk_62->z = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_62->z;
        CJProperties.unk_7A->x = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_7A->x;
        CJProperties.unk_7A->y = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_7A->y;
        CJProperties.unk_7A->z = sPlayerAgeProperties[PLAYER_FORM_FIERCE_DEITY].unk_7A->z;
        CJProperties.voiceSfxIdOffset = SFX_VOICE_BANK_SIZE * 0;
        CJProperties.surfaceSfxIdOffset = 0x80;
        sPlayerAgeProperties[PLAYER_FORM_HUMAN] = CJProperties;
        player->ageProperties = &sPlayerAgeProperties[PLAYER_FORM_HUMAN];
        *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_start) = gCJSkel_ocarinaGcj_ocarina_startAnim;
        *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_swing) = gCJSkel_ocarinaGcj_ocarina_swingAnim;
        isCjAnims = true;
    }
}

#define CJ_MASK_SCALE_MODIFIER 0.5f
#define CJ_MASK_DOWNWARDS_OFFSET -10.f
#define CJ_MASK_FORWARDS_OFSSEET 350.f
#define CJ_MASK_LATERAL_OFFSET 0.f
u8 gPushedMatrix;
extern Gfx* D_801C0B20[];
extern LinkAnimationHeader gPlayerAnim_cl_setmask;
RECOMP_HOOK("Player_PostLimbDrawGameplay") void on_Player_PostLimbDrawGameplay(PlayState* play, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot, Actor* actor) {
    if (!gIsCjLoaded) {
        return;
    }
    
    Player* player = (Player*)actor;
    if (limbIndex == PLAYER_LIMB_HEAD) {
        if (((*dList1 != NULL) && ((u32)player->currentMask != PLAYER_MASK_NONE)) &&
            (((player->transformation == PLAYER_FORM_HUMAN) &&
              ((player->skelAnime.animation != &gPlayerAnim_cl_setmask) || (player->skelAnime.curFrame >= 12.0f))) ||
             ((((player->transformation != PLAYER_FORM_HUMAN) && (player->currentMask >= PLAYER_MASK_FIERCE_DEITY)) &&
               ((player->transformation + PLAYER_MASK_FIERCE_DEITY) != player->currentMask)) &&
              (player->skelAnime.curFrame >= 10.0f)))) {   
                s32 maskMinusOne = player->currentMask - 1;
                OPEN_DISPS(play->state.gfxCtx);
                Matrix_Push();
                gPushedMatrix = 1;
                Matrix_Scale(CJ_MASK_SCALE_MODIFIER, CJ_MASK_SCALE_MODIFIER, CJ_MASK_SCALE_MODIFIER, MTXMODE_APPLY);
                Matrix_Translate(CJ_MASK_FORWARDS_OFSSEET, CJ_MASK_DOWNWARDS_OFFSET, CJ_MASK_LATERAL_OFFSET, MTXMODE_APPLY);
                MATRIX_FINALIZE_AND_LOAD(POLY_OPA_DISP++, play->state.gfxCtx);
                CLOSE_DISPS(play->state.gfxCtx);
        } else {
            gPushedMatrix = 0;
        }    
    } else {
        gPushedMatrix = 0;
    }
}

RECOMP_HOOK_RETURN("Player_PostLimbDrawGameplay") void return_Player_PostLimbDrawGameplay(void) {
    if (gPushedMatrix) {
        Matrix_Pop();
    }
    gPushedMatrix = 0;
}

extern FlexSkeletonHeader gHappyMaskSalesmanSkel;
RECOMP_HOOK("EnOsn_Init") void on_EnOsn_Init(Actor* thisx, PlayState* play) {
    if (!gIsCjLoaded) {
        return;
    }

    *(FlexSkeletonHeader*)Lib_SegmentedToVirtual(&gHappyMaskSalesmanSkel) = gBigSmokeSkel;
}

int gIsEnOsnMatrixPushed = 0;

RECOMP_HOOK ("EnOsn_Draw") void on_EnOsn_Draw(Actor* thisx, PlayState* play) {
    if (!gIsCjLoaded) {
        return;
    }

    gIsEnOsnMatrixPushed = 1;
    OPEN_DISPS(play->state.gfxCtx);
    Matrix_Push();
    Matrix_Translate(0.f, 1000.f, 0.f, MTXMODE_APPLY);
    MATRIX_FINALIZE_AND_LOAD(POLY_OPA_DISP++, play->state.gfxCtx);
    CLOSE_DISPS(play->state.gfxCtx);
}

RECOMP_HOOK_RETURN ("EnOsn_Draw") void return_EnOsn_Draw(Actor* thisx, PlayState* play) {
    if (gIsEnOsnMatrixPushed) {
        Matrix_Pop();
    }
    gIsEnOsnMatrixPushed = 0;
}

RECOMP_CALLBACK("*", recomp_on_play_main)
void mainUpdate(PlayState* play) {
    updateLink(play);
}
