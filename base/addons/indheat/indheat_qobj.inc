
* Addon  INDHEAT: contribution to QOBJ:
* Investment cost
+ IOF1000000*(SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
  (INDHEAT_VGKNACCUMNET(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)-INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP))*INDHEAT_GDATA(INDHEAT_G,'GDINVCOST0')*SUM(C$ICA(C,INDHEAT_IA),INDHEAT_ANNUITYCG(C,INDHEAT_G))
  )
  )

* Operation and maintainance cost:

   + SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)),
     INDHEAT_GDATA(INDHEAT_G,'GDOMVCOST0')
   * SUM((INDHEAT_DHUSER,IS3,T), IHOURSINST(IS3,T)* INDHEAT_VGH_T(Y,INDHEAT_IA,INDHEAT_DHUSER,INDHEAT_G,INDHEAT_GROUP,IS3,T)
$ifi not %COMBTECH%==yes $goto endcombtechOMV
         +SUM(INDHEAT_GALIAS$(INDHEAT_GGCOMB(INDHEAT_G,INDHEAT_GALIAS)), INDHEAT_VGH_T(Y,INDHEAT_IA,INDHEAT_DHUSER,INDHEAT_GALIAS,INDHEAT_GROUP,IS3,T))
$label endcombtechOMV
         ))

    + IOF1000*(SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
         (INDHEAT_VGKNACCUMNET(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP))
                 +INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP))
         *INDHEAT_GDATA(INDHEAT_G,'GDOMFCOST0')
         ))

* Cost of fuel consumption during the year:
   + SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM') AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)
$ifi not %COMBTECH%==yes $goto endcombtechFUEL1
         OR SUM(INDHEAT_GALIAS,INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G))
$label endcombtechFUEL1
         ) AND FUELPRICE(Y,INDHEAT_IA,FFF) <> 0
         AND (INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)
$ifi not %COMBTECH%==yes $goto endcombtechFUEL2
         OR SUM(INDHEAT_GALIAS$INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G), INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_GALIAS,INDHEAT_GROUP))
$label endcombtechFUEL2
         )
         ),
                 FUELPRICE(Y,INDHEAT_IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T)))

*Retrofitting TEST!!!!!
   -0.9*IOF1000*SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(SUM(INDHEAT_GROUPFROM,INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUPFROM)) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) and SUM(INDHEAT_GROUPFROM, INDHEAT_GMOVE(INDHEAT_G,INDHEAT_GROUPFROM,INDHEAT_GROUP))),
                 INDHEAT_VGKNMOVETO(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)*INDHEAT_GDATA(INDHEAT_G,'GDINVCOST0')*SUM(C$ICA(C,INDHEAT_IA),INDHEAT_ANNUITYCG(C,INDHEAT_G))
         )