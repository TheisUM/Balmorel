* hook of hydrogen between Balmorel and OptiFlow, added by Theis Madsen
* First line is for the hydrogen balancing constraint at an area level
* Second line is for the region level balancing constraint.
* This file is for AREA, another file is for REGION.


*-VFLOWBUFFER(IY411,IA,'HydrogenBuffer_MWh','HYDROGENFLOW_MWh',IS3,T)$(SUM(IPROCFROM$FLOWFROMTOPROC(IY411,IA,IPROCFROM,'HydrogenBuffer_MWh','HYDROGENFLOW_MWh'),1) OR SUM((IPROCTO)$FLOWFROMTOPROC(IY411,IA,'HydrogenBuffer_MWh',IPROCTO,'HYDROGENFLOW_MWh'),1))
+VFLOWSOURCE(IY411,IA,'HydrogenSource','HYDROGEN_FLOW',IS3,T)$(SUM(IPROCFROM$FLOWFROMTOPROC(IY411,IA,IPROCFROM,'HydrogenSource','HYDROGEN_FLOW'),1) OR SUM((IPROCTO)$FLOWFROMTOPROC(IY411,IA,'HydrogenSource',IPROCTO,'HYDROGEN_FLOW'),1))

*-SUM(IA$(RRRAAA(IR,IA) AND (SUM(IPROCFROM$FLOWFROMTOPROC(IY411,IA,IPROCFROM,'HydrogenBuffer_MWh','HYDROGEN_FLOW_MWh'),1) OR SUM((IPROCTO)$FLOWFROMTOPROC(IY411,IA,'HydrogenBuffer_MWh',IPROCTO,'HYDROGEN_FLOW_MWh'),1)) ),
*         VFLOWBUFFER(IY411,IA,'HydrogenBuffer_MWh','HYDROGEN_FLOW_MWh',IS3,T))
