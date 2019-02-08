* Loop trough all the years in the balbase4 model (goes through most of the file)
LOOP(IY411,

* TV_IY411 is the remaining years of the balbase4 model within the IY411-loop.
TV_IY411(IY411ALIAS) = NO;
TV_IY411(IY411ALIAS) = YES$(IY411.val <= IY411ALIAS.val);

* Technologies considered: investment opportunities for the current year in IY411 loop that is also in the TV_G subset.
IAGKNY_IY411(Y,IA,G) = 0;
IAGKNY_IY411(TV_IY411,IA,G) = YES$(IAGKNY(IY411,IA,G) AND TV_G(G));



**************************************
*** Defining the costs
**************************************

* Fixed costs including investment costs
TV_FIXED(TV_IY411,IA,G)$(IAGKNY_IY411(TV_IY411,IA,G))= IOF1000*GOMFCOST(IA,G)  + IOF1000000*(GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYCG(C,G))));

* Variable costs for electricity generation
TV_VAREL(TV_IY411,IA,G)$((IAGKNY(TV_IY411,IA,G) OR IAGKNY_IY411(TV_IY411,IA,G)) AND  IGNOTETOH(G) AND IGE(G))=
           GOMVCOST(IA,G)$IGKE(G)                                                                     !! variable operation costs

    + (    SUM(FFF$IGF(G,FFF), FUELPRICE(TV_IY411,IA,FFF) * IOF3P6 )                                  !! fuel costs
         + IM_CO2(G)*IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(TV_IY411,"TAX_CO2",C))                 !! CO2 costs
         + IM_SO2(G)*IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(TV_IY411,"TAX_SO2",C))                 !! SO2 costs
         + GDATA(G,'GDNOX')*IOF0000001 * SUM(C$ICA(C,IA), M_POL(TV_IY411,"TAX_NOX",C))                !! NOX costs
       )/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))

$ifi %TAXES%==yes         + SUM(C$ICA(C,IA), TAX_G_EL(TV_IY411,C,G))
$ifi %TAXES%==yes         + (SUM(C$ICA(C,IA),TAX_F_EL(TV_IY411,C,G))
$ifi %TAXES%==yes         +      SUM(C$ICA(C,IA),TAX_F(TV_IY411,C,G))  )/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))
;

*Variable cost for heat generation
TV_VARHEAT(TV_IY411,IA,G)$((IAGKNY(TV_IY411,IA,G) OR IAGKNY_IY411(TV_IY411,IA,G)) AND IGH(G))  =
                   (GOMVCOST(IA,G) * GDATA(G,'GDCV'))$IGKH(G)
                 + GDATA(G,'GDCV')* (
                   SUM(FFF$IGF(G,FFF), FUELPRICE(TV_IY411,IA,FFF) * IOF3P6 )
                 + IM_CO2(G)*IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(TV_IY411,"TAX_CO2",C))
                 + IM_SO2(G)*IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(TV_IY411,"TAX_SO2",C))
                 + GDATA(G,'GDNOX')*IOF0000001 * SUM(C$ICA(C,IA), M_POL(TV_IY411,"TAX_NOX",C))
                 )  /(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))

$ifi %TAXES%==yes      + SUM(C$ICA(C,IA),TAX_G_HEAT(TV_IY411,C,G))
$ifi %TAXES%==yes                 + (SUM(C$ICA(C,IA),TAX_F_HEAT(TV_IY411,C,G))
$ifi %TAXES%==yes                 + SUM(C$ICA(C,IA),TAX_F(TV_IY411,C,G))  )  /(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))
;


*******************************************************************************
*** idenfication of technologies with fuel or technology potential constraints
*******************************************************************************

*IGMINF
TV_REQMIN(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), IGMINF(TV_IY411,C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMIN(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IGMINF(TV_IY411,IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMIN(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), IGMINF(TV_IY411,IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*FKMIN
TV_REQMIN(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), FKMIN(TV_IY411,C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMIN(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), FKMIN(TV_IY411,IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMIN(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), FKMIN(TV_IY411,IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*IGEQF
TV_REQFX(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), IGEQF(TV_IY411,C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQFX(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IGEQF(TV_IY411,IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQFX(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), IGEQF(TV_IY411,IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*FKEQ
TV_REQFX(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), FKEQ(TV_IY411,C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQFX(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), FKEQ(TV_IY411,IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQFX(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), FKEQ(TV_IY411,IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*IGMAXF
TV_REQMAX(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), IGMAXF(TV_IY411,C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IGMAXF(TV_IY411,IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), IGMAXF(TV_IY411,IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*FKPOT
TV_REQMAX(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), FKPOT(C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), FKPOT(IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), FKPOT(IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*FKMAX
TV_REQMAX(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), FKMAX(TV_IY411,C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), FKMAX(TV_IY411,IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), FKMAX(TV_IY411,IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*TECHGROUPKPOT
TV_REQMAX(TV_IY411,IA,G)$(SUM((TECH_GROUP,C)$((GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)) AND ICA(C,IA)), TECHGROUPKPOT(C,TECH_GROUP)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM((TECH_GROUP,IR)$((GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)) AND RRRAAA(IR,IA)), TECHGROUPKPOT(IR,TECH_GROUP)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQMAX(TV_IY411,IA,G)$(SUM(TECH_GROUP$(GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)), TECHGROUPKPOT(IA,TECH_GROUP)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*FGEMIN
TV_REQEMIN(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), FGEMIN(C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQEMIN(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), FGEMIN(IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQEMIN(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), FGEMIN(IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);

*FGEMAX
TV_REQEMAX(TV_IY411,IA,G)$(SUM((FFF,C)$(IGF(G,FFF) AND ICA(C,IA)), FGEMAX(C,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQEMAX(TV_IY411,IA,G)$(SUM((FFF,IR)$(IGF(G,FFF) AND RRRAAA(IR,IA)), FGEMAX(IR,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);
TV_REQEMAX(TV_IY411,IA,G)$(SUM(FFF$IGF(G,FFF), FGEMAX(IA,FFF)) >0) = YES$IAGKNY_IY411(TV_IY411,IA,G);



**************************************************
*** Calculating and using the screening curves ***
**************************************************

** Finding the cost of the cheapest investment option in condencing power plant and heat only boiler. This is used to calculate alternative value later on.
*Cost per unit of electricity or heat generated for the cheapest plant in the screening curve without considering plants with maxium and fixed fuel requirements
TV_CHEAPESTCND(TV_IY411,IA,TV_FLH) = SMIN(G$(IGCND(G)  AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT TV_REQEMAX(TV_IY411,IA,G) AND NOT TV_REQMAX(TV_IY411,IA,G) AND NOT TV_REQFX(TV_IY411,IA,G)),
                 TV_FIXED(TV_IY411,IA,G) + TV_VAREL(TV_IY411,IA,G) * TV_FLH.VAL);
TV_CHEAPESTHOB(TV_IY411,IA,TV_FLH) = SMIN(G$(IGHOB(G)  AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT TV_REQEMAX(TV_IY411,IA,G) AND NOT TV_REQMAX(TV_IY411,IA,G) AND NOT TV_REQFX(TV_IY411,IA,G)),
                 TV_FIXED(TV_IY411,IA,G) + TV_VARHEAT(TV_IY411,IA,G) * TV_FLH.VAL);

* Finding the cost of the cheapest CND option per region
TV_CHEAPESTCNDR(TV_IY411,IR,TV_FLH) = SMIN(IA$RRRAAA(IR,IA), TV_CHEAPESTCND(TV_IY411,IA,TV_FLH));



** Calculating annual costs of serving Heat (H) or Electricity (E) under different assumptions for full load hours, full load hours for heat generation and value of "by-product" (heat when considering el-production and visa versa)
* Extraction plants
TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGEXT(G) AND IAGKNY_IY411(TV_IY411,IA,G) ) =
         TV_FIXED(TV_IY411,IA,G) * GDATA(G,'GDCB') + TV_VARHEAT(TV_IY411,IA,G) * TV_FLHHEAT.VAL + TV_VAREL(TV_IY411,IA,G) * TV_FLH.VAL*GDATA(G,'GDCB')   !! costs per MW installed heat capacity
         - TV_PR.VAL/100 * SUM(IR$RRRAAA(IR,IA), TV_CHEAPESTCNDR(TV_IY411,IR,TV_FLH))*GDATA(G,'GDCB') ;                                                  !! value of byproduct: electricity
TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGEXT(G) AND IAGKNY_IY411(TV_IY411,IA,G)) =
         TV_FIXED(TV_IY411,IA,G) + TV_VAREL(TV_IY411,IA,G) * TV_FLH.VAL + TV_VARHEAT(TV_IY411,IA,G) * TV_FLHHEAT.VAL / GDATA(G,'GDCB')                   !! costs per MW installed electricity capacity
         - TV_PR.VAL/100 * MIN(1000000, TV_CHEAPESTHOB(TV_IY411,IA,TV_FLHHEAT)) /GDATA(G,'GDCB')  ;                                                      !! value of byproduct: heat

* Back pressure plants
TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGBPR(G) AND IAGKNY_IY411(TV_IY411,IA,G))  =
         TV_FIXED(TV_IY411,IA,G) * GDATA(G,'GDCB') + TV_VARHEAT(TV_IY411,IA,G) * TV_FLH.VAL + TV_VAREL(TV_IY411,IA,G) * TV_FLH.VAL*GDATA(G,'GDCB')
         - TV_PR.VAL/100 * SUM(IR$RRRAAA(IR,IA), TV_CHEAPESTCNDR(TV_IY411,IR,TV_FLH))*GDATA(G,'GDCB') ;
TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGBPR(G) AND IAGKNY_IY411(TV_IY411,IA,G))  =
         TV_FIXED(TV_IY411,IA,G) + TV_VAREL(TV_IY411,IA,G) * TV_FLH.VAL  + TV_VARHEAT(TV_IY411,IA,G) * TV_FLH.VAL / GDATA(G,'GDCB')
         - TV_PR.VAL/100 * MIN(1000000, TV_CHEAPESTHOB(TV_IY411,IA,TV_FLHHEAT)) /GDATA(G,'GDCB')  ;

* Condencing / HOB plants
TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGHOB(G) AND IAGKNY_IY411(TV_IY411,IA,G))  = TV_FIXED(TV_IY411,IA,G) + TV_VARHEAT(TV_IY411,IA,G) * TV_FLHHEAT.VAL ;
TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGCND(G) AND IAGKNY_IY411(TV_IY411,IA,G))  = TV_FIXED(TV_IY411,IA,G) + TV_VAREL(TV_IY411,IA,G) * TV_FLH.VAL;

* Power to heat plants (bring in when having control over grid tariffs)
*TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGETOH(G) AND IAGKNY_IY411(TV_IY411,IA,G) ) = TV_FIXED(TV_IY411,IA,G) + TV_VARHEAT(TV_IY411,IA,G) * TV_FLHHEAT.VAL + TV_PR.VAL/100 * SUM(IR$RRRAAA(IR,IA), TV_CHEAPESTCNDR(TV_IY411,IR,TV_FLHHEAT))/GDATA(G,'GDFE');

* Do not consider instances when heat generation has higher full load hours than electricity generation (NB! this should not be done for CHP-technologies possibility to bypass the turbine)
TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(TV_FLHHEAT.VAL > TV_FLH.VAL) = 0;
TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(TV_FLHHEAT.VAL > TV_FLH.VAL) = 0;


** Calulating the cost of the cheapest plants
* when not considering plants affected by max and eq fuel restrictions
TV_CHEAPEST_E(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR) =
                 SMIN(G$(IGE(G) AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT TV_REQEMAX(TV_IY411,IA,G) AND NOT TV_REQMAX(TV_IY411,IA,G) AND NOT TV_REQFX(TV_IY411,IA,G)),
                         TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));
TV_CHEAPEST_H(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR) =
                 SMIN(G$(IGH(G) AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT TV_REQEMAX(TV_IY411,IA,G) AND NOT TV_REQMAX(TV_IY411,IA,G) AND NOT TV_REQFX(TV_IY411,IA,G)),
                         TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));

* when considering plants affected by max and eq fuel restrictions
TV_CHEAPEST_EF(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR) =
                 SMIN(G$(IGE(G) AND IAGKNY_IY411(TV_IY411,IA,G)), TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));
TV_CHEAPEST_HF(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR) =
                 SMIN(G$(IGH(G) AND IAGKNY_IY411(TV_IY411,IA,G)), TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));


** Identifying the cheapest plant
* when not considering plants affected by max and eq fuel restrictions
TV_CHEAPEST(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGE(G) AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT (TV_FLHHEAT.VAL > TV_FLH.VAL)
                 AND (TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = TV_CHEAPEST_E(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;
TV_CHEAPEST(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGH(G) AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT (TV_FLHHEAT.VAL > TV_FLH.VAL)
                 AND (TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = TV_CHEAPEST_H(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;

* when considering plants affected by max and eq fuel restrictions
TV_CHEAPEST(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGE(G) AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT (TV_FLHHEAT.VAL > TV_FLH.VAL)
                 AND (TV_ANNUALCOST_E(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = TV_CHEAPEST_EF(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;
TV_CHEAPEST(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGH(G) AND IAGKNY_IY411(TV_IY411,IA,G) AND NOT (TV_FLHHEAT.VAL > TV_FLH.VAL)
                 AND (TV_ANNUALCOST_H(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = TV_CHEAPEST_HF(TV_IY411,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;


** identifying the plants that are not the cheapest option in any of the cases considered
TV_NEVERCHEAP(IY411,IA,G)$(IAGKNY_IY411(IY411,IA,G) AND NOT SUM((TV_IY411,TV_FLH,TV_FLHHEAT,TV_PR), TV_CHEAPEST(TV_IY411,IA,G,TV_FLH,TV_FLHHEAT,TV_PR))) = YES;


); !! END LOOP IY411

****************************************
*** Changes to IAGKNY and IAGK_HASORPOT
****************************************

TV_NEVERCHEAP2(IY411,IA,G) = TV_NEVERCHEAP(IY411,IA,G);

* Technologies with fx or minimum fuel use requirments are NOT removed from IAGKNY:
TV_NEVERCHEAP2(IY411,IA,G)$(TV_REQEMIN(IY411,IA,G) OR TV_REQMIN(IY411,IA,G) OR TV_REQFX(IY411,IA,G)) = NO;


* Make changes to IAGKNY and IAGK_HASORPOT

IAGKNY(IY411,IA,G)$TV_NEVERCHEAP2(IY411,IA,G) = NO;
IAGK_HASORPOT(Y,IA,G) = YES$(GKFX(Y,IA,G) or IAGKNY(Y,IA,G));

*** same loop as in balmorelbb4.sim to make sure that if you invest in a technology in the year Y, you can use it until it is decommissioned, even if you do not allow for investments on this technology in the future  :
LOOP(Y$(ORD(Y) NE CARD(Y)),  LOOP(IA,  LOOP(G$IAGKNY(Y,IA,G),
                                        LOOP(IYALIAS2$((ORD(IYALIAS2) GT ORD(Y)) AND ((YVALUE(Y)+GDATA(G,'GDLIFETIME')) GT (YVALUE(IYALIAS2)))),
                                                                    IAGK_HASORPOT(Y++1,IA,G)= IAGK_HASORPOT(Y++1,IA,G)+IAGKNY(Y,IA,G);
                                        ););););





* Possibility to print some of the values for debugging
*execute_unload "../output/temp/costs.gdx", TV_fixed, TV_varel, TV_varheat, TV_REQMIN, TV_REQEMIN, TV_REQMAX, TV_REQEMAX, TV_REQFX, TV_CHEAPESTHOB, TV_CHEAPESTCND, TV_CHEAPESTCNDR,   TV_NEVERCHEAP2,IAGKNY,
* TV_NEVERCHEAP,IAGKNY_IY411, TV_CHEAPEST, IAGK_HASORPOT, TV_CHEAPEST_H, TV_CHEAPEST_E, TV_ANNUALCOST_E, TV_ANNUALCOST_H, TV_CHEAPEST_EF, TV_CHEAPEST_HF;
