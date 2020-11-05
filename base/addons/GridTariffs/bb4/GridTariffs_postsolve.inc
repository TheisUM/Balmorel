GR_FC_OUTPUT_TECH(Y,IY411,IA,IGETOH)$IY411FIRST(Y)  =

* Fixed component and subscribed power (per MW installed)

$ifi %BB4%==yes   IOF1_ *  (

                 + IOF1000 * SUM(IR, SUM(IAGK_HASORPOT(IY411,IA,IGETOH)$RRRAAA(IR,IA),

                         IGR_PRICE_TECH(IY411,IR,'GRDSUBS')  * (VGKNACCUMNET.L(IY411,IA,IGETOH) + GKFX(IY411,IA,IGETOH)) /(GDATA(IGETOH,'GDFE') *(1$(NOT GEFFRATE(IA,IGETOH))+GEFFRATE(IA,IGETOH)))     ))

);



GR_EC_OUTPUT_TECH(Y,IY411,IA,IGETOH)$IY411FIRST(Y)  =

$ifi %BB4%==yes  IOF1_ *  (

* Energy charge winter

                 + SUM(IGR_TIME('GRDECW',IR,IS3,T)$RRRAAA(IR,IA),   SUM((IAGK_HASORPOT(IY411,IA,IGETOH)),IHOURSINST(IS3,T) * IGR_PRICE_TECH(IY411,IR,'GRDECW')  * VGE_T.L(IY411,IA,IGETOH,IS3,T)))

* Energy charge summer

                 + SUM(IGR_TIME('GRDECS',IR,IS3,T)$RRRAAA(IR,IA),   SUM((IAGK_HASORPOT(IY411,IA,IGETOH)),IHOURSINST(IS3,T) * IGR_PRICE_TECH(IY411,IR,'GRDECS')  * VGE_T.L(IY411,IA,IGETOH,IS3,T)))

* Energy charge TOU step 1

                 + SUM(IGR_TIME('GRDTOU1',IR,IS3,T)$RRRAAA(IR,IA),  SUM((IAGK_HASORPOT(IY411,IA,IGETOH)),IHOURSINST(IS3,T) * IGR_PRICE_TECH(IY411,IR,'GRDTOU1')  * VGE_T.L(IY411,IA,IGETOH,IS3,T)))

* Energy charge TOU step 2

                 + SUM(IGR_TIME('GRDTOU2',IR,IS3,T)$RRRAAA(IR,IA),  SUM((IAGK_HASORPOT(IY411,IA,IGETOH)),IHOURSINST(IS3,T) * IGR_PRICE_TECH(IY411,IR,'GRDTOU2')  * VGE_T.L(IY411,IA,IGETOH,IS3,T)))

* Energy charge TOU step 3

                 + SUM(IGR_TIME('GRDTOU3',IR,IS3,T)$RRRAAA(IR,IA),  SUM((IAGK_HASORPOT(IY411,IA,IGETOH)),IHOURSINST(IS3,T) * IGR_PRICE_TECH(IY411,IR,'GRDTOU3')  * VGE_T.L(IY411,IA,IGETOH,IS3,T)))

* Energy charge TOU step 4

                 + SUM(IGR_TIME('GRDTOU4',IR,IS3,T)$RRRAAA(IR,IA),  SUM((IAGK_HASORPOT(IY411,IA,IGETOH)),IHOURSINST(IS3,T) * IGR_PRICE_TECH(IY411,IR,'GRDTOU4')  * VGE_T.L(IY411,IA,IGETOH,IS3,T)))

);



GR_DC_OUTPUT_TECH(Y,IY411,IA)$IY411FIRST(Y) =

$ifi %BB4%==yes   IOF1_ *  (

* Demand charge winter

                 + IOF1000 * SUM((IR,MMM)$(RRRAAA(IR,IA) AND SUM((IS3,T)$IGR_TIME('GRDDCW',IR,IS3,T), ISSSTTTMMM(IS3,T,MMM))), VGETOH_CAP1.L(IY411,IA,MMM) *  IGR_PRICE_TECH(IY411,IR,'GRDDCW'))/(IGR_MONTHSINSIM/card(MMM))    !! Demand charge winter

* Demand charge summer

                 + IOF1000 * SUM((IR,MMM)$(RRRAAA(IR,IA) AND SUM((IS3,T)$IGR_TIME('GRDDCS',IR,IS3,T), ISSSTTTMMM(IS3,T,MMM))), VGETOH_CAP1.L(IY411,IA,MMM) *  IGR_PRICE_TECH(IY411,IR,'GRDDCS'))/(IGR_MONTHSINSIM/card(MMM))    !! Demand charge summer

* Demand charge 2 (e.g for spring and fall months)

                 + IOF1000 * SUM((IR,MMM)$(RRRAAA(IR,IA) AND SUM((IS3,T)$IGR_TIME('GRDDC2',IR,IS3,T), ISSSTTTMMM(IS3,T,MMM))), VGETOH_CAP1.L(IY411,IA,MMM) *  IGR_PRICE_TECH(IY411,IR,'GRDDC2'))/(IGR_MONTHSINSIM/card(MMM))    !! Demand charge 2

* Demand charge TOU

                 + IOF1000 * SUM((IR,MMM)$RRRAAA(IR,IA),   VGETOH_CAP2.L(IY411,IA,MMM) *  IGR_PRICE_TECH(IY411,IR,'GRDDCTOU'))/(IGR_MONTHSINSIM/card(MMM))

* Demand charge yearly

                 + IOF1000 * SUM(IR$RRRAAA(IR,IA),   VGETOH_CAPY.L(IY411,IA) *  IGR_PRICE_TECH(IY411,IR,'GRDDCY'))

);



GR_EC_OUTPUT_USER(Y,IY411,IR,DEUSER)$IY411FIRST(Y) =

$ifi %BB4%==yes  IOF1_ *  (

* Tariffs on user groups

                 + SUM((IS3,T)$IGR_TIME('GRDECW',IR,IS3,T),   IHOURSINST(IS3,T) * IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDECW')  * VDENET_T.l(Y,IR,DEUSER,IS3,T)$(IDE_SUMST(IR,DEUSER) GT 0)  )

                 + SUM((IS3,T)$IGR_TIME('GRDECS',IR,IS3,T),   IHOURSINST(IS3,T) * IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDECS')  * VDENET_T.l(Y,IR,DEUSER,IS3,T)$(IDE_SUMST(IR,DEUSER) GT 0)   )

                 + SUM((IS3,T)$IGR_TIME('GRDTOU1',IR,IS3,T),  IHOURSINST(IS3,T) * IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDTOU1') * VDENET_T.l(Y,IR,DEUSER,IS3,T)$(IDE_SUMST(IR,DEUSER) GT 0)   )

                 + SUM((IS3,T)$IGR_TIME('GRDTOU2',IR,IS3,T),  IHOURSINST(IS3,T) * IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDTOU2') * VDENET_T.l(Y,IR,DEUSER,IS3,T)$(IDE_SUMST(IR,DEUSER) GT 0)   )

                 + SUM((IS3,T)$IGR_TIME('GRDTOU3',IR,IS3,T),  IHOURSINST(IS3,T) * IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDTOU3') * VDENET_T.l(Y,IR,DEUSER,IS3,T)$(IDE_SUMST(IR,DEUSER) GT 0)  )

                 + SUM((IS3,T)$IGR_TIME('GRDTOU4',IR,IS3,T),  IHOURSINST(IS3,T) * IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDTOU4') * VDENET_T.l(Y,IR,DEUSER,IS3,T)$(IDE_SUMST(IR,DEUSER) GT 0)   )


);




GR_DC_OUTPUT_USER(Y,IY411,IR,DEUSER)$IY411FIRST(Y) =

$ifi %BB4%==yes  IOF1_ *  (

                 + IOF1000 * SUM(MMM$(SUM((IS3,T)$IGR_TIME('GRDDCW',IR,IS3,T), ISSSTTTMMM(IS3,T,MMM))), VDEUSER_CAP1.L(IY411,IR,DEUSER,MMM) *  IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDCW'))/(IGR_MONTHSINSIM/CARD(MMM))    !! Demand charge winter

                 + IOF1000 * SUM(MMM$(SUM((IS3,T)$IGR_TIME('GRDDCS',IR,IS3,T), ISSSTTTMMM(IS3,T,MMM))), VDEUSER_CAP1.L(IY411,IR,DEUSER,MMM) *  IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDCS'))/(IGR_MONTHSINSIM/CARD(MMM))    !! Demand charge summer

                 + IOF1000 * SUM(MMM$(SUM((IS3,T)$IGR_TIME('GRDDC2',IR,IS3,T), ISSSTTTMMM(IS3,T,MMM))), VDEUSER_CAP1.L(IY411,IR,DEUSER,MMM) *  IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDC2'))/(IGR_MONTHSINSIM/CARD(MMM))    !! Demand charge 2

                 + IOF1000 * SUM(MMM,   VDEUSER_CAP2.L(IY411,IR,DEUSER,MMM) *  IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDCTOU'))/(IGR_MONTHSINSIM/card(MMM))

                 + IOF1000 * VDEUSER_CAPY.L(IY411,IR,DEUSER) *  IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDCY')

);


* Prepare inter-model Grid tariff data for scenario 3 and 4
$ifi %SCENARIO3OR4%==YES $goto label_GridTariffs_postsolve_SCEN34_END

* total grid tariffs payed in sc 1 or 2 per technology:
GR_FC_INPUTOUT_TECH(Y,Y,IA) = SUM(IGETOH, GR_FC_OUTPUT_TECH(Y,Y,IA,IGETOH) + GR_EC_OUTPUT_TECH(Y,Y,IA,IGETOH)) + GR_DC_OUTPUT_TECH(Y,Y,IA)  ;

* total grid tariffs payed in sc 1 or 2 per user group
$ifi not %SCENARIO34_ALT%==YES GR_FC_INPUTOUT_USER(Y,Y,IR,DEUSER) = GR_EC_OUTPUT_USER(Y,Y,IR,DEUSER) + GR_DC_OUTPUT_USER(Y,Y,IR,DEUSER);
$ifi %SCENARIO34_ALT%==YES GR_FC_INPUTOUT_USER(Y,Y,IR,'PII') = GR_EC_OUTPUT_USER(Y,Y,IR,'PII') + GR_DC_OUTPUT_USER(Y,Y,IR,'PII');

* calculate the aggregate load profile for all power to heat units in Scenario 1 and 2.
GR_GETOH_VAR_T(Y,S,T) = SUM((IA,IGETOH)$(GKFX(Y,IA,IGETOH) OR VGKNACCUMNET.L(Y,IA,IGETOH)), VGE_T.L(Y,IA,IGETOH,S,T));
GR_GETOH_VAR_TCT(Y,TECH_GROUP,S,T) = SUM((IA,IGETOH)$((GKFX(Y,IA,IGETOH) OR VGKNACCUMNET.L(Y,IA,IGETOH)) AND (GDATA(IGETOH,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP))), VGE_T.L(Y,IA,IGETOH,S,T));

* Calculate installed capacity for all power to heat units in Scenario 1 and 2.
GR_GETOH_FX(Y) = SUM((IA,IGETOH), (GKFX(Y,IA,IGETOH) + VGKNACCUMNET.L(Y,IA,IGETOH)) /(GDATA(IGETOH,'GDFE') *(1$(NOT GEFFRATE(IA,IGETOH))+GEFFRATE(IA,IGETOH))));
GR_GETOH_TCFX(Y,TECH_GROUP)   = SUM((IA,IGETOH)$(GDATA(IGETOH,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)), (GKFX(Y,IA,IGETOH) + VGKNACCUMNET.L(Y,IA,IGETOH)) /(GDATA(IGETOH,'GDFE') *(1$(NOT GEFFRATE(IA,IGETOH))+GEFFRATE(IA,IGETOH))));

* Calculate the capacity usage for the demand charges
GR_GETOH_CAP1(Y,MMM) = SMAX((S,T)$ISSSTTTMMM(S,T,MMM), GR_GETOH_VAR_T(Y,S,T));
GR_GETOH_CAP2(Y,C,MMM) = SMAX((S,T)$ISSSTTTMMM(S,T,MMM), GR_GETOH_VAR_T(Y,S,T)$SUM(IR$CCCRRR(C,IR), IGR_TIME('GRDDCTOU',IR,S,T)));
GR_GETOH_CAPY(Y,C) = SMAX((S,T),  GR_GETOH_VAR_T(Y,S,T)$SUM(IR$CCCRRR(C,IR), IGR_TIME('GRDDCY',IR,S,T)));


* Calculate total grid tariffs payed per country given the aggregated load profile for P2H.
GR_GETOH_TOTAL(Y,C) =

$ifi %BB4%==yes   IOF1_ *  (

                 + IOF1000 * SMAX(IR$CCCRRR(C,IR),  IGR_PRICE_TECH(Y,IR,'GRDSUBS')  * GR_GETOH_FX(Y)    )                                                         !! Fixed charge / subscribed charge

                 + SMAX(IR$CCCRRR(C,IR),  IGR_PRICE_TECH(Y,IR,'GRDECW')) * SUM((S,T)$SMAX(IR$CCCRRR(C,IR), IGR_TIME('GRDECW',IR,S,T)), IHOURSINST(S,T)*GR_GETOH_VAR_T(Y,S,T))    !! Energy charge winter

                 + SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDECS'))  * SUM((S,T)$SMAX(IR$CCCRRR(C,IR), IGR_TIME('GRDECS',IR,S,T)), IHOURSINST(S,T)*GR_GETOH_VAR_T(Y,S,T))    !! Energy charge summer

                 + SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDTOU1')) * SUM((S,T)$SMAX(IR$CCCRRR(C,IR), IGR_TIME('GRDTOU1',IR,S,T)), IHOURSINST(S,T)*GR_GETOH_VAR_T(Y,S,T))   !! Energy charge TOU step 1

                 + SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDTOU2')) * SUM((S,T)$SMAX(IR$CCCRRR(C,IR), IGR_TIME('GRDTOU2',IR,S,T)), IHOURSINST(S,T)*GR_GETOH_VAR_T(Y,S,T))   !! Energy charge TOU step 2

                 + SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDTOU3')) * SUM((S,T)$SMAX(IR$CCCRRR(C,IR), IGR_TIME('GRDTOU3',IR,S,T)), IHOURSINST(S,T)*GR_GETOH_VAR_T(Y,S,T))   !! Energy charge TOU step 3

                 + SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDTOU4')) * SUM((S,T)$SMAX(IR$CCCRRR(C,IR), IGR_TIME('GRDTOU4',IR,S,T)), IHOURSINST(S,T)*GR_GETOH_VAR_T(Y,S,T))   !! Energy charge TOU step 4

* Demand charges:
                 + IOF1000 * SUM(MMM$(IGR_MONTHSINSIM2(MMM) AND SUM((S,T)$SMAX(IR$CCCRRR(C,IR), IGR_TIME('GRDDCW',IR,S,T)), ISSSTTTMMM(S,T,MMM))), GR_GETOH_CAP1(Y,MMM) *  SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDDCW')))/(IGR_MONTHSINSIM/card(MMM))    !! Demand charge winter

                 + IOF1000 * SUM(MMM$(IGR_MONTHSINSIM2(MMM) AND SUM((S,T)$SMAX(IR$CCCRRR(C,IR),IGR_TIME('GRDDCS',IR,S,T)), ISSSTTTMMM(S,T,MMM))), GR_GETOH_CAP1(Y,MMM) *  SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDDCS')))/(IGR_MONTHSINSIM/card(MMM))    !! Demand charge summer

                 + IOF1000 * SUM(MMM$(IGR_MONTHSINSIM2(MMM) AND SUM((S,T)$SMAX(IR$CCCRRR(C,IR),IGR_TIME('GRDDC2',IR,S,T)), ISSSTTTMMM(S,T,MMM))), GR_GETOH_CAP1(Y,MMM) *  SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDDC2')))/(IGR_MONTHSINSIM/card(MMM))    !! Demand charge 2

                 + IOF1000 * SUM(MMM$IGR_MONTHSINSIM2(MMM),   GR_GETOH_CAP2(Y,C,MMM)  *  SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDDCTOU')))/(IGR_MONTHSINSIM/card(MMM))

                 + IOF1000 *   GR_GETOH_CAPY(Y,C) *  SMAX(IR$CCCRRR(C,IR), IGR_PRICE_TECH(Y,IR,'GRDDCY'))

);

* Then the capacity based tariff is calculated as follows:
GR_GETOH_PRICE(Y,C)  =  GR_GETOH_TOTAL(Y,C) / GR_GETOH_FX(Y);

* Tax that is transferred from Scenario 1 or 2 to scenario 3 or 4:
$ifi not %SCENARIO3OR4%==YES $ifi %TAXES%==YES TAX_GETOH(Y,C) =  SUM((S,T,TECH_GROUP)$GR_GETOH_TCFX(Y,TECH_GROUP), SMAX(IGETOH$(GDATA(IGETOH,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)), TAX_F_HEAT(Y,C,IGETOH)) * IHOURSINST(S,T)  * GR_GETOH_VAR_TCT(Y,TECH_GROUP,S,T)) /   GR_GETOH_FX(Y);



** saving the file for scenario 3
$ifi %SCENARIO1%==YES EXECUTE_UNLOAD  "../../simex/GR_FC_1.gdx" GR_FC_INPUTOUT_TECH, GR_FC_INPUTOUT_USER, GR_GETOH_VAR_T, GR_GETOH_VAR_TCT, GR_GETOH_TCFX, GR_GETOH_FX, GR_GETOH_CAP1, GR_GETOH_CAP2, GR_GETOH_CAPY, GR_GETOH_TOTAL, GR_GETOH_PRICE
$ifi %SCENARIO1%==YES $ifi %TAXES%==YES TAX_GETOH
;

** saving the file for scenario 4
$ifi %SCENARIO2%==YES EXECUTE_UNLOAD  "../../simex/GR_FC_2.gdx" GR_FC_INPUTOUT_TECH, GR_FC_INPUTOUT_USER, GR_GETOH_VAR_T, GR_GETOH_VAR_TCT, GR_GETOH_TCFX, GR_GETOH_FX, GR_GETOH_CAP1, GR_GETOH_CAP2, GR_GETOH_CAPY, GR_GETOH_TOTAL, GR_GETOH_PRICE
$ifi %SCENARIO2%==YES $ifi %TAXES%==YES TAX_GETOH
;

** End calculations taken from scenario 1 or 2 to scenario 3 or 4
$LABEL label_GridTariffs_postsolve_SCEN34_END

** loading the file for scenario 3
$ifi %SCENARIO3OR4%==YES $ifi %SCENARIO3%==YES EXECUTE_LOAD "../../simex/GR_FC_1.gdx"   GR_FC_INPUTOUT_USER;
$ifi %SCENARIO3OR4%==YES $ifi %SCENARIO3%==YES GR_FC_OUTPUT_USER(Y,Y,IR,DEUSER) = MAX(0, GR_FC_INPUTOUT_USER(Y,Y,IR,DEUSER) - GR_EC_OUTPUT_USER(Y,Y,IR,DEUSER) -  GR_DC_OUTPUT_USER(Y,Y,IR,DEUSER));

** loading the file for scenario 4
$ifi %SCENARIO3OR4%==YES  $ifi %SCENARIO4%==YES EXECUTE_LOAD "../../simex/GR_FC_2.gdx"   GR_FC_INPUTOUT_USER;
$ifi %SCENARIO3OR4%==YES  $ifi %SCENARIO4%==YES GR_FC_OUTPUT_USER(Y,Y,IR,DEUSER) = MAX(0, GR_FC_INPUTOUT_USER(Y,Y,IR,DEUSER) - GR_EC_OUTPUT_USER(Y,Y,IR,DEUSER) -  GR_DC_OUTPUT_USER(Y,Y,IR,DEUSER));



EXECUTE_UNLOAD "%relpathtemp%/GR_OUT.gdx", GR_FC_OUTPUT_TECH, GR_EC_OUTPUT_TECH, GR_DC_OUTPUT_TECH, GR_EC_OUTPUT_USER, GR_DC_OUTPUT_USER, GR_FC_OUTPUT_USER;
