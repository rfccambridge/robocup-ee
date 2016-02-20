<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="16" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="14" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="tplace-old" color="10" fill="1" visible="yes" active="yes"/>
<layer number="109" name="ref-old" color="11" fill="1" visible="yes" active="yes"/>
<layer number="110" name="fp0" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="LPC17xx" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="IDFDebug" color="4" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="yes" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="154" name="FabDoc2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="155" name="FabDoc3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="225" name="225bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="226" name="226bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="227" name="227bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="228" name="228bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="229" name="229bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="230" name="230bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="231" name="231bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="routoute" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="SparkFun-Capacitors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find resistors, capacitors, inductors, test points, jumper pads, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="CAP-PTH-SMALL">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651"/>
<text x="0.508" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="0.254" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="CAP-PTH-SMALL2">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="3.81" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="-1.27" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651"/>
<text x="-1.27" y="1.905" size="0.6096" layer="25">&gt;Name</text>
<text x="-1.27" y="-2.54" size="0.6096" layer="27">&gt;Value</text>
</package>
<package name="0805">
<wire x1="-0.3" y1="0.6" x2="0.3" y2="0.6" width="0.1524" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="-0.6" width="0.1524" layer="21"/>
<smd name="1" x="-0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<smd name="2" x="0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<text x="-0.762" y="0.8255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="CAP-PTH-LARGE">
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.2032" layer="21"/>
<pad name="1" x="-4.826" y="0" drill="0.9" diameter="1.905"/>
<pad name="2" x="4.572" y="0" drill="0.9" diameter="1.905"/>
<text x="-0.762" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.016" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="GRM43D">
<wire x1="2.25" y1="1.6" x2="1.1" y2="1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="1.6" x2="-1.1" y2="1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="1.6" x2="-2.25" y2="1.6" width="0.127" layer="51"/>
<wire x1="-2.25" y1="1.6" x2="-2.25" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-2.25" y1="-1.6" x2="-1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="-1.6" x2="1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="-1.6" x2="2.25" y2="-1.6" width="0.127" layer="51"/>
<wire x1="2.25" y1="-1.6" x2="2.25" y2="1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="1.6" x2="1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="1.6" x2="-1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-2.3" y1="1.8" x2="2.3" y2="1.8" width="0.127" layer="21"/>
<wire x1="-2.3" y1="-1.8" x2="2.3" y2="-1.8" width="0.127" layer="21"/>
<smd name="A" x="1.927" y="0" dx="3.2" dy="1.65" layer="1" rot="R90"/>
<smd name="C" x="-1.927" y="0" dx="3.2" dy="1.65" layer="1" rot="R90"/>
<text x="-2" y="2" size="0.4064" layer="25">&gt;NAME</text>
<text x="0" y="-2" size="0.4064" layer="27" rot="R180">&gt;VALUE</text>
<rectangle x1="-2.2" y1="-1.6" x2="-1.1" y2="1.6" layer="51"/>
<rectangle x1="1.1" y1="-1.6" x2="2.2" y2="1.6" layer="51"/>
</package>
<package name="0603-CAP">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<wire x1="0" y1="0.0305" x2="0" y2="-0.0305" width="0.5588" layer="21"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="0402-CAP">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="0" y1="0.0305" x2="0" y2="-0.0305" width="0.4064" layer="21"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="CAP-PTH-5MM">
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.5" y="0" drill="0.7" diameter="1.651"/>
<text x="-0.762" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.016" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="AXIAL-5MM">
<wire x1="-1.14" y1="0.762" x2="1.14" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0.762" x2="1.14" y2="0" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0" x2="1.14" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="-0.762" x2="-1.14" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="-0.762" x2="-1.14" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="0" x2="-1.14" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0" x2="1.394" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="0" x2="-1.394" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-2.5" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="2.5" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.17" size="0.4" layer="25">&gt;Name</text>
<text x="-1.032" y="-0.208" size="0.4" layer="21" ratio="15">&gt;Value</text>
</package>
<package name="1210">
<wire x1="-1.6" y1="1.3" x2="1.6" y2="1.3" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.3" x2="1.6" y2="-1.3" width="0.127" layer="51"/>
<wire x1="1.6" y1="-1.3" x2="-1.6" y2="-1.3" width="0.127" layer="51"/>
<wire x1="-1.6" y1="-1.3" x2="-1.6" y2="1.3" width="0.127" layer="51"/>
<wire x1="-1.6" y1="1.3" x2="1.6" y2="1.3" width="0.2032" layer="21"/>
<wire x1="-1.6" y1="-1.3" x2="1.6" y2="-1.3" width="0.2032" layer="21"/>
<smd name="1" x="-1.6" y="0" dx="1.2" dy="2" layer="1"/>
<smd name="2" x="1.6" y="0" dx="1.2" dy="2" layer="1"/>
<text x="-0.8" y="0.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.9" y="-0.7" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1206">
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-0.965" y1="0.787" x2="0.965" y2="0.787" width="0.1016" layer="51"/>
<wire x1="-0.965" y1="-0.787" x2="0.965" y2="-0.787" width="0.1016" layer="51"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-1.27" y="1.143" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.397" y="-1.524" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-1.7018" y1="-0.8509" x2="-0.9517" y2="0.8491" layer="51"/>
<rectangle x1="0.9517" y1="-0.8491" x2="1.7018" y2="0.8509" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
<package name="CTZ3">
<description>CTZ3 Series land pattern for variable capacitor - CTZ3E-50C-W1-PF</description>
<wire x1="-1.6" y1="1.4" x2="-1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-1.6" y1="-2.25" x2="1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.4" x2="1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-0.5" y1="0" x2="0.5" y2="0" width="0.127" layer="51"/>
<wire x1="-1.6" y1="1.4" x2="-1" y2="2.2" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.4" x2="1" y2="2.2" width="0.127" layer="51"/>
<wire x1="-1" y1="2.2" x2="1" y2="2.2" width="0.127" layer="51"/>
<wire x1="0" y1="0.8" x2="0" y2="-0.8" width="0.127" layer="51"/>
<wire x1="-0.8" y1="0" x2="0.8" y2="0" width="0.127" layer="51"/>
<wire x1="-1.05" y1="2.25" x2="-1.7" y2="1.45" width="0.127" layer="21"/>
<wire x1="-1.7" y1="1.45" x2="-1.7" y2="-2.35" width="0.127" layer="21"/>
<wire x1="-1.7" y1="-2.35" x2="-1.05" y2="-2.35" width="0.127" layer="21"/>
<wire x1="1.05" y1="2.25" x2="1.7" y2="1.4" width="0.127" layer="21"/>
<wire x1="1.7" y1="1.4" x2="1.7" y2="-2.35" width="0.127" layer="21"/>
<wire x1="1.7" y1="-2.35" x2="1.05" y2="-2.35" width="0.127" layer="21"/>
<smd name="+" x="0" y="2.05" dx="1.5" dy="1.2" layer="1"/>
<smd name="-" x="0" y="-2.05" dx="1.5" dy="1.2" layer="1"/>
<text x="-2" y="3" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2" y="-3.4" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="CAP-PTH-SMALL-KIT">
<description>&lt;h3&gt;CAP-PTH-SMALL-KIT&lt;/h3&gt;
Commonly used for small ceramic capacitors. Like our 0.1uF (http://www.sparkfun.com/products/8375) or 22pF caps (http://www.sparkfun.com/products/8571).&lt;br&gt;
&lt;br&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.254" layer="21"/>
<wire x1="-2.667" y1="1.27" x2="2.667" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.667" y1="1.27" x2="2.667" y2="-1.27" width="0.254" layer="21"/>
<wire x1="2.667" y1="-1.27" x2="-2.667" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-2.667" y1="-1.27" x2="-2.667" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-1.397" y="0" drill="1.016" diameter="2.032" stop="no"/>
<pad name="2" x="1.397" y="0" drill="1.016" diameter="2.032" stop="no"/>
<polygon width="0.127" layer="30">
<vertex x="-1.4021" y="-0.9475" curve="-90"/>
<vertex x="-2.357" y="-0.0178" curve="-90.011749"/>
<vertex x="-1.4046" y="0.9576" curve="-90"/>
<vertex x="-0.4546" y="-0.0204" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-1.4046" y="-0.4395" curve="-90.012891"/>
<vertex x="-1.8491" y="-0.0153" curve="-90"/>
<vertex x="-1.4046" y="0.452" curve="-90"/>
<vertex x="-0.9627" y="-0.0051" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="1.397" y="-0.9475" curve="-90"/>
<vertex x="0.4421" y="-0.0178" curve="-90.011749"/>
<vertex x="1.3945" y="0.9576" curve="-90"/>
<vertex x="2.3445" y="-0.0204" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="1.3945" y="-0.4395" curve="-90.012891"/>
<vertex x="0.95" y="-0.0153" curve="-90"/>
<vertex x="1.3945" y="0.452" curve="-90"/>
<vertex x="1.8364" y="-0.0051" curve="-90.012967"/>
</polygon>
</package>
<package name="CAP-PTH-SMALLEZ">
<description>This is the "EZ" version of the .1" spaced ceramic thru-hole cap.&lt;br&gt;
It has reduced top mask to make it harder to put the component on the wrong side of the board.</description>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="3.81" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="-1.27" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7" diameter="1.651" stop="no"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651" stop="no"/>
<text x="-1.27" y="1.905" size="0.6096" layer="25">&gt;Name</text>
<text x="-1.27" y="-2.54" size="0.6096" layer="27">&gt;Value</text>
<circle x="0" y="0" radius="0.898025" width="0" layer="30"/>
<circle x="2.54" y="0" radius="0.915809375" width="0" layer="30"/>
<circle x="0" y="0" radius="0.40160625" width="0" layer="29"/>
<circle x="2.54" y="0" radius="0.40160625" width="0" layer="29"/>
</package>
</packages>
<symbols>
<symbol name="CAP">
<wire x1="0" y1="2.54" x2="0" y2="2.032" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="0.508" width="0.1524" layer="94"/>
<text x="1.524" y="2.921" size="1.778" layer="95">&gt;NAME</text>
<text x="1.524" y="-2.159" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="0.508" x2="2.032" y2="1.016" layer="94"/>
<rectangle x1="-2.032" y1="1.524" x2="2.032" y2="2.032" layer="94"/>
<pin name="1" x="0" y="5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CAP" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor&lt;/b&gt;
Standard 0603 ceramic capacitor, and 0.1" leaded capacitor.</description>
<gates>
<gate name="G$1" symbol="CAP" x="0" y="0"/>
</gates>
<devices>
<device name="PTH" package="CAP-PTH-SMALL">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CAP-PTH-SMALL2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH3" package="CAP-PTH-LARGE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="GRM43D">
<connects>
<connect gate="G$1" pin="1" pad="A"/>
<connect gate="G$1" pin="2" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603-CAP" package="0603-CAP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402-CAP" package="0402-CAP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CAP-PTH-5MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_" package="AXIAL-5MM">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1210" package="1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="ASMD" package="CTZ3">
<connects>
<connect gate="G$1" pin="1" pad="+"/>
<connect gate="G$1" pin="2" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT" package="CAP-PTH-SMALL-KIT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EZ" package="CAP-PTH-SMALLEZ">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-wago-500">
<description>&lt;b&gt;Wago Screw Clamps&lt;/b&gt;&lt;p&gt;
Grid 5.00 mm&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="W237-102">
<description>&lt;b&gt;WAGO SCREW CLAMP&lt;/b&gt;</description>
<wire x1="-3.491" y1="-2.286" x2="-1.484" y2="-0.279" width="0.254" layer="51"/>
<wire x1="1.488" y1="-2.261" x2="3.469" y2="-0.254" width="0.254" layer="51"/>
<wire x1="-4.989" y1="-5.461" x2="4.993" y2="-5.461" width="0.1524" layer="21"/>
<wire x1="4.993" y1="3.734" x2="4.993" y2="3.531" width="0.1524" layer="21"/>
<wire x1="4.993" y1="3.734" x2="-4.989" y2="3.734" width="0.1524" layer="21"/>
<wire x1="-4.989" y1="-5.461" x2="-4.989" y2="-3.073" width="0.1524" layer="21"/>
<wire x1="-4.989" y1="-3.073" x2="-3.389" y2="-3.073" width="0.1524" layer="21"/>
<wire x1="-3.389" y1="-3.073" x2="-1.611" y2="-3.073" width="0.1524" layer="51"/>
<wire x1="-1.611" y1="-3.073" x2="1.615" y2="-3.073" width="0.1524" layer="21"/>
<wire x1="3.393" y1="-3.073" x2="4.993" y2="-3.073" width="0.1524" layer="21"/>
<wire x1="-4.989" y1="-3.073" x2="-4.989" y2="3.531" width="0.1524" layer="21"/>
<wire x1="4.993" y1="-3.073" x2="4.993" y2="-5.461" width="0.1524" layer="21"/>
<wire x1="-4.989" y1="3.531" x2="4.993" y2="3.531" width="0.1524" layer="21"/>
<wire x1="-4.989" y1="3.531" x2="-4.989" y2="3.734" width="0.1524" layer="21"/>
<wire x1="4.993" y1="3.531" x2="4.993" y2="-3.073" width="0.1524" layer="21"/>
<wire x1="1.615" y1="-3.073" x2="3.393" y2="-3.073" width="0.1524" layer="51"/>
<circle x="-2.5" y="-1.27" radius="1.4986" width="0.1524" layer="51"/>
<circle x="-2.5" y="2.2098" radius="0.508" width="0.1524" layer="21"/>
<circle x="2.5038" y="-1.27" radius="1.4986" width="0.1524" layer="51"/>
<circle x="2.5038" y="2.2098" radius="0.508" width="0.1524" layer="21"/>
<pad name="1" x="-2.5" y="-1.27" drill="1.1938" shape="long" rot="R90"/>
<pad name="2" x="2.5" y="-1.27" drill="1.1938" shape="long" rot="R90"/>
<text x="-5.04" y="-7.62" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-3.8462" y="-5.0038" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.532" y="0.635" size="1.27" layer="21" ratio="10">1</text>
<text x="0.421" y="0.635" size="1.27" layer="21" ratio="10">2</text>
</package>
</packages>
<symbols>
<symbol name="KL">
<circle x="1.27" y="0" radius="1.27" width="0.254" layer="94"/>
<text x="0" y="0.889" size="1.778" layer="95" rot="R180">&gt;NAME</text>
<pin name="KL" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="KL+V">
<circle x="1.27" y="0" radius="1.27" width="0.254" layer="94"/>
<text x="-2.54" y="-3.683" size="1.778" layer="96">&gt;VALUE</text>
<text x="0" y="0.889" size="1.778" layer="95" rot="R180">&gt;NAME</text>
<pin name="KL" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="W237-102" prefix="X" uservalue="yes">
<description>&lt;b&gt;WAGO SCREW CLAMP&lt;/b&gt;</description>
<gates>
<gate name="-1" symbol="KL" x="0" y="5.08" addlevel="always"/>
<gate name="-2" symbol="KL+V" x="0" y="0" addlevel="always"/>
</gates>
<devices>
<device name="" package="W237-102">
<connects>
<connect gate="-1" pin="KL" pad="1"/>
<connect gate="-2" pin="KL" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="237-102" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="70K9898" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="gen3">
<packages>
<package name="CK_SWITCH">
<description>&lt;b&gt; SPDT Switch &lt;/b&gt;&lt;p&gt;</description>
<pad name="COM" x="0" y="0" drill="2" diameter="3.302" shape="square"/>
<pad name="IN1" x="4.699" y="0" drill="2" diameter="3.302" shape="square"/>
<pad name="IN2" x="-4.699" y="0" drill="2" diameter="3.302" shape="square"/>
<pad name="SUP1" x="-6.604" y="-9.525" drill="2" diameter="2.54" shape="square"/>
<pad name="SUP2" x="6.604" y="-9.525" drill="2" diameter="2.54" shape="square"/>
<wire x1="-8.89" y1="-11.43" x2="-8.89" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-8.89" y1="-2.54" x2="8.89" y2="-2.54" width="0.127" layer="21"/>
<wire x1="8.89" y1="-2.54" x2="8.89" y2="-11.43" width="0.127" layer="21"/>
<wire x1="8.89" y1="-11.43" x2="7.62" y2="-11.43" width="0.127" layer="21"/>
<wire x1="7.62" y1="-11.43" x2="0" y2="-11.43" width="0.127" layer="21"/>
<wire x1="0" y1="-11.43" x2="-8.89" y2="-11.43" width="0.127" layer="21"/>
<wire x1="0" y1="-11.43" x2="0" y2="-15.24" width="0.127" layer="21"/>
<wire x1="0" y1="-15.24" x2="7.62" y2="-15.24" width="0.127" layer="21"/>
<wire x1="7.62" y1="-15.24" x2="7.62" y2="-11.43" width="0.127" layer="21"/>
<text x="-3.81" y="-6.35" size="1.27" layer="25">&gt;NAME</text>
</package>
<package name="TESTING_PT">
<pad name="P$1" x="0" y="0" drill="0.8"/>
<wire x1="-1" y1="1" x2="-1" y2="-1" width="0.127" layer="21"/>
<wire x1="-1" y1="-1" x2="1" y2="-1" width="0.127" layer="21"/>
<wire x1="1" y1="-1" x2="1" y2="1" width="0.127" layer="21"/>
<wire x1="1" y1="1" x2="-1" y2="1" width="0.127" layer="21"/>
<text x="0" y="1.5" size="0.8128" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.31" size="0.8128" layer="26" rot="MR0" align="bottom-center">&gt;NAME</text>
</package>
<package name="DPAK">
<description>DPAK FET</description>
<wire x1="3.4" y1="-3.4" x2="-3.4" y2="-3.4" width="0.127" layer="21"/>
<wire x1="-3.4" y1="-3.4" x2="-3.4" y2="3.4" width="0.127" layer="21"/>
<wire x1="-3.4" y1="3.4" x2="3.4" y2="3.4" width="0.127" layer="21"/>
<wire x1="3.4" y1="3.4" x2="3.4" y2="2.8" width="0.127" layer="21"/>
<wire x1="3.4" y1="2.8" x2="4.2" y2="2.8" width="0.127" layer="21"/>
<wire x1="4.2" y1="1.8" x2="3.4" y2="1.8" width="0.127" layer="21"/>
<wire x1="3.4" y1="1.8" x2="3.4" y2="-1.8" width="0.127" layer="21"/>
<wire x1="3.4" y1="-1.8" x2="4.2" y2="-1.8" width="0.127" layer="21"/>
<wire x1="4.2" y1="-2.8" x2="3.4" y2="-2.8" width="0.127" layer="21"/>
<wire x1="3.4" y1="-2.8" x2="3.4" y2="-3.4" width="0.127" layer="21"/>
<smd name="DRAIN" x="0" y="0" dx="6.7" dy="6.7" layer="1"/>
<smd name="SOURCE" x="5.75" y="2.3" dx="3" dy="1.6" layer="1"/>
<smd name="GATE" x="5.75" y="-2.3" dx="3" dy="1.6" layer="1"/>
<text x="2" y="4" size="0.7" layer="27" font="vector" ratio="10">&gt;VALUE</text>
<text x="-3" y="4" size="0.7" layer="25" font="vector" ratio="10">&gt;NAME</text>
<rectangle x1="-3.4" y1="-3.4" x2="3.4" y2="3.4" layer="39"/>
<rectangle x1="4.2" y1="-3.1" x2="7.3" y2="-1.5" layer="39"/>
<rectangle x1="4.2" y1="1.5" x2="7.3" y2="3.1" layer="39"/>
</package>
<package name="SMB-DIODE">
<description>&lt;b&gt;Diode&lt;/b&gt;&lt;p&gt;
Basic small signal diode good up to 200mA. SMB footprint. Common part #: BAS16</description>
<wire x1="-3.973" y1="1.983" x2="3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="-1.983" x2="-3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-3.973" y1="-1.983" x2="-3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="1.983" x2="3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-2.2606" y1="1.905" x2="2.2606" y2="1.905" width="0.1016" layer="21"/>
<wire x1="-2.2606" y1="-1.905" x2="2.2606" y2="-1.905" width="0.1016" layer="21"/>
<wire x1="-2.261" y1="-1.905" x2="-2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="2.261" y1="-1.905" x2="2.261" y2="1.905" width="0.1016" layer="51"/>
<wire x1="0.643" y1="1" x2="-0.73" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="0" x2="0.643" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.643" y1="-1" x2="0.643" y2="1" width="0.2032" layer="21"/>
<wire x1="-0.73" y1="1" x2="-0.73" y2="-1" width="0.2032" layer="21"/>
<smd name="C" x="-2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<smd name="A" x="2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<text x="-2.159" y="2.159" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.429" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.794" y1="-1.0922" x2="-2.2606" y2="1.0922" layer="51"/>
<rectangle x1="2.2606" y1="-1.0922" x2="2.794" y2="1.0922" layer="51"/>
</package>
<package name="SOD-323">
<wire x1="-0.9" y1="0.65" x2="-0.5" y2="0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.65" x2="0.9" y2="0.65" width="0.2032" layer="21"/>
<wire x1="-0.9" y1="-0.65" x2="-0.5" y2="-0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="-0.65" x2="0.9" y2="-0.65" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.65" x2="-0.5" y2="-0.65" width="0.2032" layer="21"/>
<smd name="C" x="-1.15" y="0" dx="0.63" dy="0.83" layer="1"/>
<smd name="A" x="1.15" y="0" dx="0.63" dy="0.83" layer="1"/>
<text x="-0.889" y="1.016" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="SOD-123">
<description>100V/150mA 1N4148 - Super Cheap</description>
<wire x1="-1.3" y1="0.775" x2="-0.5" y2="0.775" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.775" x2="1.3" y2="0.775" width="0.2032" layer="21"/>
<wire x1="-1.3" y1="-0.775" x2="-0.5" y2="-0.775" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="-0.775" x2="1.3" y2="-0.775" width="0.2032" layer="21"/>
<wire x1="-0.5" y1="0.775" x2="-0.5" y2="-0.775" width="0.2032" layer="21"/>
<smd name="C" x="-1.575" y="0" dx="0.9" dy="0.95" layer="1"/>
<smd name="A" x="1.575" y="0" dx="0.9" dy="0.95" layer="1"/>
<text x="-0.889" y="1.016" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
<wire x1="-1.35" y1="0.775" x2="1.35" y2="0.775" width="0.127" layer="51"/>
<wire x1="1.35" y1="0.775" x2="1.35" y2="-0.775" width="0.127" layer="51"/>
<wire x1="1.35" y1="-0.775" x2="-1.35" y2="-0.775" width="0.127" layer="51"/>
<wire x1="-1.35" y1="-0.775" x2="-1.35" y2="0.775" width="0.127" layer="51"/>
</package>
<package name="DO214AC">
<description>&lt;b&gt;DIODE&lt;/b&gt;</description>
<wire x1="-2.3" y1="1" x2="2.3" y2="1" width="0.254" layer="51"/>
<wire x1="2.3" y1="1" x2="2.3" y2="-0.95" width="0.254" layer="51"/>
<wire x1="2.3" y1="-0.95" x2="-2.3" y2="-0.95" width="0.254" layer="51"/>
<wire x1="-2.3" y1="-0.95" x2="-2.3" y2="1" width="0.254" layer="51"/>
<wire x1="-0.8" y1="0" x2="0.25" y2="0.75" width="0.254" layer="21"/>
<wire x1="0.25" y1="0.75" x2="0.25" y2="-0.7" width="0.254" layer="21"/>
<wire x1="0.25" y1="-0.7" x2="-0.8" y2="0" width="0.254" layer="21"/>
<smd name="C" x="-2.05" y="0" dx="1.8" dy="1.7" layer="1"/>
<smd name="A" x="2.05" y="0" dx="1.8" dy="1.7" layer="1"/>
<text x="-2.64" y="1.286" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.64" y="-2.556" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-2.65" y1="-0.7" x2="-2.4" y2="0.65" layer="51"/>
<rectangle x1="2.4" y1="-0.7" x2="2.65" y2="0.65" layer="51"/>
<rectangle x1="-1" y1="-1.05" x2="-0.7" y2="1.05" layer="21"/>
</package>
<package name="DO214AA">
<description>&lt;b&gt;DIODE&lt;/b&gt;</description>
<wire x1="-2.4" y1="1.1" x2="2.4" y2="1.1" width="0.254" layer="51"/>
<wire x1="2.4" y1="1.1" x2="2.4" y2="-1.1" width="0.254" layer="51"/>
<wire x1="2.4" y1="-1.1" x2="-2.4" y2="-1.1" width="0.254" layer="51"/>
<wire x1="-2.4" y1="-1.1" x2="-2.4" y2="1.1" width="0.254" layer="51"/>
<wire x1="-1.2" y1="0" x2="0.05" y2="0.7" width="0.254" layer="21"/>
<wire x1="0.05" y1="0.7" x2="0.05" y2="-0.7" width="0.254" layer="21"/>
<wire x1="0.05" y1="-0.7" x2="-1.2" y2="0" width="0.254" layer="21"/>
<smd name="C" x="-2.55" y="0" dx="1.8" dy="2.2" layer="1"/>
<smd name="A" x="2.55" y="0" dx="1.8" dy="2.2" layer="1"/>
<text x="-2.64" y="1.436" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.64" y="-2.706" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-2.75" y1="-0.7" x2="-2.5" y2="0.65" layer="51"/>
<rectangle x1="2.5" y1="-0.7" x2="2.75" y2="0.65" layer="51"/>
<rectangle x1="-1.4" y1="-1.05" x2="-1.1" y2="1.05" layer="21"/>
</package>
<package name="DO214AB">
<smd name="ANODE" x="0" y="3.1115" dx="2.54" dy="3.556" layer="1"/>
<smd name="CATHODE" x="7.112" y="3.1115" dx="2.54" dy="3.556" layer="1"/>
<wire x1="0" y1="0.508" x2="0" y2="5.715" width="0.127" layer="21"/>
<wire x1="0" y1="5.715" x2="0.508" y2="6.223" width="0.127" layer="21" curve="-90"/>
<wire x1="0.508" y1="6.223" x2="6.604" y2="6.223" width="0.127" layer="25"/>
<wire x1="6.604" y1="6.223" x2="7.112" y2="5.715" width="0.127" layer="21" curve="-90"/>
<wire x1="7.112" y1="5.715" x2="7.112" y2="0.508" width="0.127" layer="21"/>
<wire x1="7.112" y1="0.508" x2="6.604" y2="0" width="0.127" layer="21" curve="-90"/>
<wire x1="6.604" y1="0" x2="0.508" y2="0" width="0.127" layer="21"/>
<wire x1="0.508" y1="0" x2="0" y2="0.508" width="0.127" layer="21" curve="-90"/>
<text x="0" y="6.35" size="1.27" layer="21">&gt;NAME</text>
<rectangle x1="-0.508" y1="1.5113" x2="1.016" y2="4.7117" layer="21"/>
<rectangle x1="6.096" y1="1.5113" x2="7.62" y2="4.7117" layer="21"/>
<wire x1="1.27" y1="3.175" x2="2.54" y2="3.175" width="0.127" layer="21"/>
<wire x1="2.54" y1="3.175" x2="2.54" y2="4.445" width="0.127" layer="21"/>
<wire x1="2.54" y1="3.175" x2="2.54" y2="1.905" width="0.127" layer="21"/>
<wire x1="2.54" y1="1.905" x2="3.81" y2="3.175" width="0.127" layer="21"/>
<wire x1="3.81" y1="3.175" x2="2.54" y2="4.445" width="0.127" layer="21"/>
<wire x1="3.81" y1="5.08" x2="3.81" y2="3.175" width="0.127" layer="21"/>
<wire x1="3.81" y1="3.175" x2="3.81" y2="1.27" width="0.127" layer="21"/>
<wire x1="3.81" y1="5.08" x2="3.175" y2="5.08" width="0.127" layer="21"/>
<wire x1="3.175" y1="5.08" x2="3.175" y2="4.445" width="0.127" layer="21"/>
<wire x1="3.81" y1="1.27" x2="4.445" y2="1.27" width="0.127" layer="21"/>
<wire x1="3.81" y1="3.175" x2="5.715" y2="3.175" width="0.127" layer="21"/>
<wire x1="4.445" y1="1.27" x2="4.445" y2="1.905" width="0.127" layer="21"/>
<text x="0" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="DO214BA">
<description>&lt;b&gt;DIODE&lt;/b&gt;</description>
<wire x1="-2.5" y1="1.35" x2="2.5" y2="1.35" width="0.254" layer="51"/>
<wire x1="2.5" y1="1.35" x2="2.5" y2="-1.35" width="0.254" layer="51"/>
<wire x1="2.5" y1="-1.35" x2="-2.5" y2="-1.35" width="0.254" layer="51"/>
<wire x1="-2.5" y1="-1.35" x2="-2.5" y2="1.35" width="0.254" layer="51"/>
<wire x1="-0.8" y1="0" x2="0.65" y2="0.95" width="0.254" layer="21"/>
<wire x1="0.65" y1="0.95" x2="0.65" y2="-0.95" width="0.254" layer="21"/>
<wire x1="0.65" y1="-0.95" x2="-0.8" y2="0" width="0.254" layer="21"/>
<smd name="C" x="-2.05" y="0" dx="1.8" dy="1.7" layer="1"/>
<smd name="A" x="2.05" y="0" dx="1.8" dy="1.7" layer="1"/>
<text x="-2.64" y="1.736" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.64" y="-3.056" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-2.85" y1="-0.7" x2="-2.6" y2="0.65" layer="51"/>
<rectangle x1="2.6" y1="-0.7" x2="2.85" y2="0.65" layer="51"/>
<rectangle x1="-1" y1="-1.05" x2="-0.7" y2="1.05" layer="21"/>
</package>
<package name="JST-2-2MM">
<pad name="2" x="-1" y="1" drill="1"/>
<pad name="1" x="1" y="1" drill="1" shape="square"/>
<wire x1="-3" y1="2" x2="-3" y2="-5" width="0.127" layer="21"/>
<wire x1="-3" y1="-5" x2="0" y2="-5" width="0.127" layer="21"/>
<wire x1="0" y1="-5" x2="3" y2="-5" width="0.127" layer="21"/>
<wire x1="3" y1="-5" x2="3" y2="2" width="0.127" layer="21"/>
<wire x1="3" y1="2" x2="-3" y2="2" width="0.127" layer="21"/>
<wire x1="0" y1="-5" x2="0" y2="-2" width="0.127" layer="21"/>
<text x="0" y="3" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
</package>
<package name="JST-5-2MM">
<description>&lt;b&gt;JST 2mm x5&lt;/b&gt; &lt;p&gt;
connector</description>
<pad name="1" x="4" y="0" drill="0.8" shape="square"/>
<pad name="2" x="2" y="0" drill="0.8"/>
<pad name="3" x="0" y="0" drill="0.8"/>
<pad name="4" x="-2" y="0" drill="0.8"/>
<pad name="5" x="-4" y="0" drill="0.8"/>
<wire x1="6" y1="1" x2="-6" y2="1" width="0.127" layer="21"/>
<wire x1="-6" y1="1" x2="-6" y2="-4" width="0.127" layer="21"/>
<wire x1="-6" y1="-4" x2="-5" y2="-4" width="0.127" layer="21"/>
<wire x1="-5" y1="-4" x2="-3" y2="-4" width="0.127" layer="21"/>
<wire x1="-3" y1="-4" x2="-1" y2="-4" width="0.127" layer="21"/>
<wire x1="-1" y1="-4" x2="1" y2="-4" width="0.127" layer="21"/>
<wire x1="1" y1="-4" x2="3" y2="-4" width="0.127" layer="21"/>
<wire x1="3" y1="-4" x2="5" y2="-4" width="0.127" layer="21"/>
<wire x1="5" y1="-4" x2="6" y2="-4" width="0.127" layer="21"/>
<wire x1="6" y1="-4" x2="6" y2="1" width="0.127" layer="21"/>
<wire x1="-3" y1="-4" x2="-3" y2="-3" width="0.127" layer="21"/>
<wire x1="-1" y1="-4" x2="-1" y2="-3" width="0.127" layer="21"/>
<wire x1="1" y1="-4" x2="1" y2="-3" width="0.127" layer="21"/>
<wire x1="3" y1="-4" x2="3" y2="-3" width="0.127" layer="21"/>
<wire x1="5" y1="-4" x2="5" y2="-3" width="0.127" layer="21"/>
<wire x1="-5" y1="-4" x2="-5" y2="-3" width="0.127" layer="21"/>
<text x="0" y="2" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="SPDT-SWITCH">
<description>&lt;b&gt;SPDT Switch &lt;/b&gt;</description>
<pin name="COM" x="-10.16" y="0" visible="pad" length="middle"/>
<pin name="P1" x="10.16" y="5.08" visible="pad" length="middle" rot="R180"/>
<pin name="P2" x="10.16" y="-5.08" visible="pad" length="middle" rot="R180"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="6.35" y2="3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="5.08" width="0.254" layer="94"/>
<text x="-5.08" y="6.35" size="1.27" layer="94">&gt;NAME</text>
<text x="-10.16" y="-2.54" size="1.27" layer="94">&gt;VALUE</text>
</symbol>
<symbol name="TEST_PT">
<description>&lt;b&gt;Testing Point&lt;/b&gt;&lt;p&gt;
provides an easy access for an oscilloscope probe</description>
<pin name="P$1" x="0" y="-2.54" visible="off" length="short" rot="R90"/>
<text x="-3.81" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<circle x="0" y="1.27" radius="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="3.3REG1A">
<wire x1="-5.08" y1="-7.62" x2="7.62" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="7.62" y2="7.62" width="0.4064" layer="94"/>
<wire x1="7.62" y1="7.62" x2="-5.08" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="-7.62" width="0.4064" layer="94"/>
<text x="-5.08" y="9.144" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-11.43" size="1.778" layer="96">&gt;VALUE</text>
<pin name="IN" x="-7.62" y="5.08" visible="pin" length="short" direction="in"/>
<pin name="OUT" x="-7.62" y="-5.08" visible="pin" length="short"/>
<pin name="GND" x="10.16" y="0" visible="pin" length="short" rot="R180"/>
</symbol>
<symbol name="DIODE-ZENER">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.778" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0.762" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<pin name="A" x="-2.54" y="0" visible="off" length="point" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="point" direction="pas" rot="R180"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="1.27" y2="0" width="0.1524" layer="94"/>
</symbol>
<symbol name="MOSFET">
<wire x1="0.508" y1="1.778" x2="2.54" y2="1.778" width="0.127" layer="94"/>
<wire x1="2.54" y1="1.778" x2="5.08" y2="1.778" width="0.127" layer="94"/>
<wire x1="5.08" y1="1.778" x2="5.08" y2="0.762" width="0.127" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.08" y2="-1.778" width="0.127" layer="94"/>
<wire x1="5.08" y1="-1.778" x2="2.54" y2="-1.778" width="0.127" layer="94"/>
<wire x1="2.54" y1="-1.778" x2="0.508" y2="-1.778" width="0.127" layer="94"/>
<wire x1="1.524" y1="0" x2="2.54" y2="0" width="0.127" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-1.778" width="0.127" layer="94"/>
<wire x1="4.572" y1="0.762" x2="5.08" y2="0.762" width="0.127" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.588" y2="0.762" width="0.127" layer="94"/>
<wire x1="5.588" y1="0.762" x2="5.842" y2="1.016" width="0.127" layer="94"/>
<wire x1="4.572" y1="0.762" x2="4.318" y2="0.508" width="0.127" layer="94"/>
<wire x1="5.08" y1="0.762" x2="4.572" y2="-0.254" width="0.127" layer="94"/>
<wire x1="4.572" y1="-0.254" x2="5.588" y2="-0.254" width="0.127" layer="94"/>
<wire x1="5.588" y1="-0.254" x2="5.08" y2="0.762" width="0.127" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="-1.27" y2="-2.54" width="0.127" layer="94"/>
<wire x1="2.54" y1="-1.778" x2="2.54" y2="-2.54" width="0.127" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="1.778" width="0.127" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="94"/>
<text x="6.35" y="2.54" size="0.7" layer="95" font="vector" ratio="10">&gt;NAME</text>
<text x="6.35" y="-1.524" size="0.7" layer="95" font="vector" ratio="10">&gt;VALUE</text>
<rectangle x1="-0.508" y1="-0.762" x2="0.508" y2="0.762" layer="94"/>
<rectangle x1="-0.508" y1="-2.54" x2="0.508" y2="-1.016" layer="94"/>
<rectangle x1="-0.508" y1="1.016" x2="0.508" y2="2.54" layer="94"/>
<pin name="D" x="2.54" y="5.08" visible="off" length="short" rot="R270"/>
<pin name="S" x="2.54" y="-5.08" visible="off" length="short" rot="R90"/>
<pin name="G" x="-5.08" y="-2.54" visible="off" length="short"/>
<polygon width="0.127" layer="94">
<vertex x="0.508" y="0"/>
<vertex x="1.524" y="0.508"/>
<vertex x="1.524" y="-0.508"/>
</polygon>
</symbol>
<symbol name="JST-2">
<pin name="P$1" x="-5.08" y="2.54" visible="pad" length="middle"/>
<pin name="P$2" x="-5.08" y="-2.54" visible="pad" length="middle"/>
<wire x1="0" y1="5.08" x2="0" y2="-5.08" width="0.254" layer="94"/>
<wire x1="0" y1="-5.08" x2="7.62" y2="-5.08" width="0.254" layer="94"/>
<wire x1="7.62" y1="-5.08" x2="7.62" y2="5.08" width="0.254" layer="94"/>
<wire x1="7.62" y1="5.08" x2="0" y2="5.08" width="0.254" layer="94"/>
<text x="-2.54" y="-7.62" size="1.778" layer="95">&gt;NAME</text>
</symbol>
<symbol name="JST-5">
<pin name="P$1" x="-7.62" y="10.16" visible="pad" length="middle"/>
<pin name="P$2" x="-7.62" y="5.08" visible="pad" length="middle"/>
<pin name="P$3" x="-7.62" y="0" visible="pad" length="middle"/>
<pin name="P$4" x="-7.62" y="-5.08" visible="pad" length="middle"/>
<pin name="P$5" x="-7.62" y="-10.16" visible="pad" length="middle"/>
<wire x1="-2.54" y1="12.7" x2="-2.54" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-12.7" x2="5.08" y2="-12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="-12.7" x2="5.08" y2="12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="12.7" x2="-2.54" y2="12.7" width="0.254" layer="94"/>
<text x="2.54" y="0" size="1.778" layer="95" rot="R90" align="bottom-center">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="SPDT-SWITCH">
<gates>
<gate name="G$1" symbol="SPDT-SWITCH" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CK_SWITCH">
<connects>
<connect gate="G$1" pin="COM" pad="COM"/>
<connect gate="G$1" pin="P1" pad="IN1"/>
<connect gate="G$1" pin="P2" pad="IN2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="TEST_PT">
<description>&lt;b&gt;Testing Point&lt;/b&gt;&lt;p&gt;
Use to probe a signal</description>
<gates>
<gate name="G$1" symbol="TEST_PT" x="0" y="-2.54"/>
</gates>
<devices>
<device name="" package="TESTING_PT">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="3.3REG1A">
<gates>
<gate name="G$1" symbol="3.3REG1A" x="0" y="0"/>
</gates>
<devices>
<device name="REG" package="DPAK">
<connects>
<connect gate="G$1" pin="GND" pad="DRAIN"/>
<connect gate="G$1" pin="IN" pad="GATE"/>
<connect gate="G$1" pin="OUT" pad="SOURCE"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DIODE-ZENER" prefix="D">
<description>Zener Diode
Production Part - 8199
3.4V Zener Voltage</description>
<gates>
<gate name="G$1" symbol="DIODE-ZENER" x="0" y="0"/>
</gates>
<devices>
<device name="SMB" package="SMB-DIODE">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.3V" package="SOD-323">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="DIO-11284"/>
<attribute name="VALUE" value="3.3V" constant="no"/>
</technology>
</technologies>
</device>
<device name="SOD-123" package="SOD-123">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DO214AC" package="DO214AC">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DO214AA" package="DO214AA">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DO214AB" package="DO214AB">
<connects>
<connect gate="G$1" pin="A" pad="ANODE"/>
<connect gate="G$1" pin="C" pad="CATHODE"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DO214BA" package="DO214BA">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="N-MOSFET" prefix="Q" uservalue="yes">
<description>N-Channel Power Mosfet</description>
<gates>
<gate name="G$1" symbol="MOSFET" x="0" y="0"/>
</gates>
<devices>
<device name="DPAK" package="DPAK">
<connects>
<connect gate="G$1" pin="D" pad="DRAIN"/>
<connect gate="G$1" pin="G" pad="GATE"/>
<connect gate="G$1" pin="S" pad="SOURCE"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="JST-2">
<gates>
<gate name="G$1" symbol="JST-2" x="-2.54" y="0"/>
</gates>
<devices>
<device name="2MM" package="JST-2-2MM">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="JST-5">
<gates>
<gate name="G$1" symbol="JST-5" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JST-5-2MM">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
<connect gate="G$1" pin="P$3" pad="3"/>
<connect gate="G$1" pin="P$4" pad="4"/>
<connect gate="G$1" pin="P$5" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Passives">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find resistors, capacitors, inductors, test points, jumper pads, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="1206">
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-0.965" y1="0.787" x2="0.965" y2="0.787" width="0.1016" layer="51"/>
<wire x1="-0.965" y1="-0.787" x2="0.965" y2="-0.787" width="0.1016" layer="51"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-1.27" y="1.143" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.397" y="-1.524" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-1.7018" y1="-0.8509" x2="-0.9517" y2="0.8491" layer="51"/>
<rectangle x1="0.9517" y1="-0.8491" x2="1.7018" y2="0.8509" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
<package name="AXIAL-0.3">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="3.81" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.032" y="-0.381" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="R2010">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.1524" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.1524" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="-1.027" y1="1.245" x2="1.027" y2="1.245" width="0.1524" layer="21"/>
<wire x1="-1.002" y1="-1.245" x2="1.016" y2="-1.245" width="0.1524" layer="21"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-2.54" y="1.5875" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.032" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
</package>
<package name="0805">
<wire x1="-0.3" y1="0.6" x2="0.3" y2="0.6" width="0.1524" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="-0.6" width="0.1524" layer="21"/>
<smd name="1" x="-0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<smd name="2" x="0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<text x="-0.762" y="0.8255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="0603-RES">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2286" y1="-0.381" x2="0.2286" y2="0.381" layer="21"/>
</package>
<package name="0402-RES">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2032" y1="-0.3556" x2="0.2032" y2="0.3556" layer="21"/>
</package>
<package name="1/6W-RES">
<description>1/6W Thru-hole Resistor - *UNPROVEN*</description>
<wire x1="-1.55" y1="0.85" x2="-1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="-1.55" y1="-0.85" x2="1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="-0.85" x2="1.55" y2="0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="0.85" x2="-1.55" y2="0.85" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.762"/>
<pad name="2" x="2.5" y="0" drill="0.762"/>
<text x="-1.2662" y="0.9552" size="0.6096" layer="25">&gt;NAME</text>
<text x="-1.423" y="-0.4286" size="0.8128" layer="21" ratio="15">&gt;VALUE</text>
</package>
<package name="R2512">
<wire x1="-2.362" y1="1.473" x2="2.387" y2="1.473" width="0.1524" layer="51"/>
<wire x1="-2.362" y1="-1.473" x2="2.387" y2="-1.473" width="0.1524" layer="51"/>
<smd name="1" x="-2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<smd name="2" x="2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.2004" y1="-1.5494" x2="-2.3505" y2="1.5507" layer="51"/>
<rectangle x1="2.3622" y1="-1.5494" x2="3.2121" y2="1.5507" layer="51"/>
</package>
<package name="AXIAL-0.4">
<description>1/4W Resistor, 0.4" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-3.15" y1="-1.2" x2="-3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3.15" y1="1.2" x2="3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="1.2" x2="3.15" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="-1.2" x2="-3.15" y2="-1.2" width="0.2032" layer="21"/>
<pad name="P$1" x="-5.08" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="5.08" y="0" drill="0.9" diameter="1.8796"/>
<text x="-3.175" y="1.905" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-2.286" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.5">
<description>1/2W Resistor, 0.5" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-4.5" y1="-1.65" x2="-4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="1.65" x2="4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="1.65" x2="4.5" y2="-1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-1.65" x2="-4.5" y2="-1.65" width="0.2032" layer="21"/>
<pad name="P$1" x="-6.35" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="6.35" y="0" drill="0.9" diameter="1.8796"/>
<text x="-4.445" y="2.54" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-3.429" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.6">
<description>1W Resistor, 0.6" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-5.75" y1="-2.25" x2="-5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="-5.75" y1="2.25" x2="5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="2.25" x2="5.75" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="-2.25" x2="-5.75" y2="-2.25" width="0.2032" layer="21"/>
<pad name="P$1" x="-7.62" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="7.62" y="0" drill="1.2" diameter="1.8796"/>
<text x="-5.715" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-4.064" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.8">
<description>2W Resistor, 0.8" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-7.75" y1="-2.5" x2="-7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-7.75" y1="2.5" x2="7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="2.5" x2="7.75" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="-2.5" x2="-7.75" y2="-2.5" width="0.2032" layer="21"/>
<pad name="P$1" x="-10.16" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="10.16" y="0" drill="1.2" diameter="1.8796"/>
<text x="-7.62" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-5.969" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.3-KIT">
<description>&lt;h3&gt;AXIAL-0.3-KIT&lt;/h3&gt;

Commonly used for 1/4W through-hole resistors. 0.3" pitch between holes.&lt;br&gt;
&lt;br&gt;

&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of the AXIAL-0.3 package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="0" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="-2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.254" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<pad name="P$2" x="3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.159" y="-0.762" size="1.27" layer="21" font="vector" ratio="15">&gt;Value</text>
<polygon width="0.127" layer="30">
<vertex x="3.8201" y="-0.9449" curve="-90"/>
<vertex x="2.8652" y="-0.0152" curve="-90.011749"/>
<vertex x="3.8176" y="0.9602" curve="-90"/>
<vertex x="4.7676" y="-0.0178" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="3.8176" y="-0.4369" curve="-90.012891"/>
<vertex x="3.3731" y="-0.0127" curve="-90"/>
<vertex x="3.8176" y="0.4546" curve="-90"/>
<vertex x="4.2595" y="-0.0025" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="-3.8075" y="-0.9525" curve="-90"/>
<vertex x="-4.7624" y="-0.0228" curve="-90.011749"/>
<vertex x="-3.81" y="0.9526" curve="-90"/>
<vertex x="-2.86" y="-0.0254" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-3.81" y="-0.4445" curve="-90.012891"/>
<vertex x="-4.2545" y="-0.0203" curve="-90"/>
<vertex x="-3.81" y="0.447" curve="-90"/>
<vertex x="-3.3681" y="-0.0101" curve="-90.012967"/>
</polygon>
</package>
<package name="AXIAL-0.3EZ">
<description>This is the "EZ" version of the standard .3" spaced resistor package.&lt;br&gt;
It has a reduced top mask to make it harder to install upside-down.</description>
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<pad name="P$2" x="3.81" y="0" drill="0.9" diameter="1.8796" stop="no"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.032" y="-0.381" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
<circle x="-3.81" y="0" radius="0.508" width="0" layer="29"/>
<circle x="3.81" y="0" radius="0.523634375" width="0" layer="29"/>
<circle x="-3.81" y="0" radius="1.02390625" width="0" layer="30"/>
<circle x="3.81" y="0" radius="1.04726875" width="0" layer="30"/>
</package>
</packages>
<symbols>
<symbol name="RESISTOR">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.1524" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.1524" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="RESISTOR" prefix="R" uservalue="yes">
<description>&lt;b&gt;Resistor&lt;/b&gt;
Basic schematic elements and footprints for 0603, 1206, and PTH resistors.</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AXIAL-0.3" package="AXIAL-0.3">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2010" package="R2010">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805-RES" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603-RES" package="0603-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402-RES" package="0402-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/6W" package="1/6W-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2512" package="R2512">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/4W" package="AXIAL-0.4">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/2W" package="AXIAL-0.5">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1W" package="AXIAL-0.6">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-2W" package="AXIAL-0.8">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT" package="AXIAL-0.3-KIT">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EZ" package="AXIAL-0.3EZ">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diode">
<description>&lt;b&gt;Diodes&lt;/b&gt;&lt;p&gt;
Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Motorola : www.onsemi.com
&lt;li&gt;Fairchild : www.fairchildsemi.com
&lt;li&gt;Philips : www.semiconductors.com
&lt;li&gt;Vishay : www.vishay.de
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SOD323_ST">
<description>&lt;b&gt;SOD-323&lt;/b&gt;&lt;p&gt;
Source: www.st.com, BAT60J.pdf</description>
<wire x1="-0.85" y1="0.55" x2="0.85" y2="0.55" width="0.1016" layer="21"/>
<wire x1="0.85" y1="0.55" x2="0.85" y2="-0.55" width="0.1016" layer="51"/>
<wire x1="0.85" y1="-0.55" x2="-0.85" y2="-0.55" width="0.1016" layer="21"/>
<wire x1="-0.85" y1="-0.55" x2="-0.85" y2="0.55" width="0.1016" layer="51"/>
<smd name="C" x="-1.25" y="0" dx="0.8" dy="0.6" layer="1"/>
<smd name="A" x="1.25" y="0" dx="0.8" dy="0.6" layer="1"/>
<text x="-1.65" y="0.75" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.65" y="-2" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.65" y1="-0.55" x2="-0.05" y2="0.55" layer="21"/>
<rectangle x1="-1.35" y1="-0.15" x2="-0.8" y2="0.15" layer="51"/>
<rectangle x1="0.8" y1="-0.15" x2="1.35" y2="0.15" layer="51"/>
<rectangle x1="-0.85" y1="-0.55" x2="-0.05" y2="0.55" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="SCHOTTKY">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="1.016" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="-1.016" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<text x="-2.286" y="1.905" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.286" y="-3.429" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="BAT60J" prefix="D">
<description>&lt;b&gt;Schottky barrier diode&lt;/b&gt;&lt;p&gt;
Source: www.st.com, BAT60J.pdf</description>
<gates>
<gate name="G$1" symbol="SCHOTTKY" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOD323_ST">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Connectors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find connectors and sockets- basically anything that can be plugged into or onto.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="1X10">
<wire x1="14.605" y1="1.27" x2="15.875" y2="1.27" width="0.2032" layer="21"/>
<wire x1="15.875" y1="1.27" x2="16.51" y2="0.635" width="0.2032" layer="21"/>
<wire x1="16.51" y1="-0.635" x2="15.875" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="11.43" y1="0.635" x2="12.065" y2="1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="1.27" x2="13.335" y2="1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="1.27" x2="13.97" y2="0.635" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="13.335" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="-1.27" x2="12.065" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="-1.27" x2="11.43" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="14.605" y1="1.27" x2="13.97" y2="0.635" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="14.605" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="15.875" y1="-1.27" x2="14.605" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="8.255" y2="1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="1.27" x2="8.89" y2="0.635" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.635" x2="8.255" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.635" x2="9.525" y2="1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.795" y2="1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="1.27" x2="11.43" y2="0.635" width="0.2032" layer="21"/>
<wire x1="11.43" y1="-0.635" x2="10.795" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="-1.27" x2="9.525" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.89" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="17.145" y1="1.27" x2="18.415" y2="1.27" width="0.2032" layer="21"/>
<wire x1="18.415" y1="1.27" x2="19.05" y2="0.635" width="0.2032" layer="21"/>
<wire x1="19.05" y1="-0.635" x2="18.415" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="17.145" y1="1.27" x2="16.51" y2="0.635" width="0.2032" layer="21"/>
<wire x1="16.51" y1="-0.635" x2="17.145" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="18.415" y1="-1.27" x2="17.145" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="19.685" y1="1.27" x2="20.955" y2="1.27" width="0.2032" layer="21"/>
<wire x1="20.955" y1="1.27" x2="21.59" y2="0.635" width="0.2032" layer="21"/>
<wire x1="21.59" y1="-0.635" x2="20.955" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="19.685" y1="1.27" x2="19.05" y2="0.635" width="0.2032" layer="21"/>
<wire x1="19.05" y1="-0.635" x2="19.685" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="20.955" y1="-1.27" x2="19.685" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="22.225" y1="1.27" x2="23.495" y2="1.27" width="0.2032" layer="21"/>
<wire x1="23.495" y1="1.27" x2="24.13" y2="0.635" width="0.2032" layer="21"/>
<wire x1="24.13" y1="0.635" x2="24.13" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="24.13" y1="-0.635" x2="23.495" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="22.225" y1="1.27" x2="21.59" y2="0.635" width="0.2032" layer="21"/>
<wire x1="21.59" y1="-0.635" x2="22.225" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="23.495" y1="-1.27" x2="22.225" y2="-1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="6" x="12.7" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="7" x="15.24" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="8" x="17.78" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="9" x="20.32" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="10" x="22.86" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="14.986" y1="-0.254" x2="15.494" y2="0.254" layer="51"/>
<rectangle x1="12.446" y1="-0.254" x2="12.954" y2="0.254" layer="51"/>
<rectangle x1="9.906" y1="-0.254" x2="10.414" y2="0.254" layer="51"/>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="17.526" y1="-0.254" x2="18.034" y2="0.254" layer="51"/>
<rectangle x1="20.066" y1="-0.254" x2="20.574" y2="0.254" layer="51"/>
<rectangle x1="22.606" y1="-0.254" x2="23.114" y2="0.254" layer="51"/>
</package>
<package name="1X10-2MM">
<wire x1="-1.25" y1="1.25" x2="19.25" y2="1.25" width="0.2032" layer="21"/>
<wire x1="19.25" y1="-1.25" x2="-1.25" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="1.25" x2="-1.25" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="19.25" y1="1.25" x2="19.25" y2="-1.25" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.8" shape="square" rot="R90"/>
<pad name="2" x="2" y="0" drill="0.8" rot="R90"/>
<pad name="3" x="4" y="0" drill="0.8" rot="R90"/>
<pad name="4" x="6" y="0" drill="0.8" rot="R90"/>
<pad name="5" x="8" y="0" drill="0.8" rot="R90"/>
<pad name="6" x="10" y="0" drill="0.8" rot="R90"/>
<pad name="7" x="12" y="0" drill="0.8" rot="R90"/>
<pad name="8" x="14" y="0" drill="0.8" rot="R90"/>
<pad name="9" x="16" y="0" drill="0.8" rot="R90"/>
<pad name="10" x="18" y="0" drill="0.8" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="3.746" y1="-0.254" x2="4.254" y2="0.254" layer="51"/>
<rectangle x1="1.746" y1="-0.254" x2="2.254" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="5.746" y1="-0.254" x2="6.254" y2="0.254" layer="51"/>
<rectangle x1="7.746" y1="-0.254" x2="8.254" y2="0.254" layer="51"/>
<rectangle x1="9.746" y1="-0.254" x2="10.254" y2="0.254" layer="51"/>
<rectangle x1="11.746" y1="-0.254" x2="12.254" y2="0.254" layer="51"/>
<rectangle x1="13.746" y1="-0.254" x2="14.254" y2="0.254" layer="51"/>
<rectangle x1="15.746" y1="-0.254" x2="16.254" y2="0.254" layer="51"/>
<rectangle x1="17.746" y1="-0.254" x2="18.254" y2="0.254" layer="51"/>
</package>
<package name="1X10-2MM-SMD">
<wire x1="-1.25" y1="1.25" x2="19.25" y2="1.25" width="0.2032" layer="51"/>
<wire x1="19.25" y1="-1.25" x2="-1.25" y2="-1.25" width="0.2032" layer="51"/>
<wire x1="-1.25" y1="1.25" x2="-1.25" y2="-1.25" width="0.2032" layer="51"/>
<wire x1="19.25" y1="1.25" x2="19.25" y2="-1.25" width="0.2032" layer="51"/>
<wire x1="-1.25" y1="1.25" x2="-0.7" y2="1.25" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="1.25" x2="-1.25" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="-1.25" x2="-0.7" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="18.6" y1="-1.25" x2="19.25" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="19.25" y1="-1.25" x2="19.25" y2="1.25" width="0.2032" layer="21"/>
<wire x1="19.25" y1="1.25" x2="18.6" y2="1.25" width="0.2032" layer="21"/>
<smd name="1" x="0" y="-1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="2" x="2" y="1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="3" x="4" y="-1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="4" x="6" y="1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="5" x="8" y="-1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="6" x="10" y="1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="7" x="12" y="-1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="8" x="14" y="1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="9" x="16" y="-1.5" dx="0.85" dy="2.1" layer="1"/>
<smd name="10" x="18" y="1.5" dx="0.85" dy="2.1" layer="1"/>
<text x="1.143" y="1.524" size="0.4064" layer="25" ratio="10">&gt;NAME</text>
<text x="4.953" y="1.524" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="1X10_LOCK">
<wire x1="14.605" y1="1.27" x2="15.875" y2="1.27" width="0.2032" layer="21"/>
<wire x1="15.875" y1="1.27" x2="16.51" y2="0.635" width="0.2032" layer="21"/>
<wire x1="16.51" y1="-0.635" x2="15.875" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="11.43" y1="0.635" x2="12.065" y2="1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="1.27" x2="13.335" y2="1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="1.27" x2="13.97" y2="0.635" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="13.335" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="13.335" y1="-1.27" x2="12.065" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="12.065" y1="-1.27" x2="11.43" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="14.605" y1="1.27" x2="13.97" y2="0.635" width="0.2032" layer="21"/>
<wire x1="13.97" y1="-0.635" x2="14.605" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="15.875" y1="-1.27" x2="14.605" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="8.255" y2="1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="1.27" x2="8.89" y2="0.635" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.635" x2="8.255" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.635" x2="9.525" y2="1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.795" y2="1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="1.27" x2="11.43" y2="0.635" width="0.2032" layer="21"/>
<wire x1="11.43" y1="-0.635" x2="10.795" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="10.795" y1="-1.27" x2="9.525" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.89" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="17.145" y1="1.27" x2="18.415" y2="1.27" width="0.2032" layer="21"/>
<wire x1="18.415" y1="1.27" x2="19.05" y2="0.635" width="0.2032" layer="21"/>
<wire x1="19.05" y1="-0.635" x2="18.415" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="17.145" y1="1.27" x2="16.51" y2="0.635" width="0.2032" layer="21"/>
<wire x1="16.51" y1="-0.635" x2="17.145" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="18.415" y1="-1.27" x2="17.145" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="19.685" y1="1.27" x2="20.955" y2="1.27" width="0.2032" layer="21"/>
<wire x1="20.955" y1="1.27" x2="21.59" y2="0.635" width="0.2032" layer="21"/>
<wire x1="21.59" y1="-0.635" x2="20.955" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="19.685" y1="1.27" x2="19.05" y2="0.635" width="0.2032" layer="21"/>
<wire x1="19.05" y1="-0.635" x2="19.685" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="20.955" y1="-1.27" x2="19.685" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="22.225" y1="1.27" x2="23.495" y2="1.27" width="0.2032" layer="21"/>
<wire x1="23.495" y1="1.27" x2="24.13" y2="0.635" width="0.2032" layer="21"/>
<wire x1="24.13" y1="0.635" x2="24.13" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="24.13" y1="-0.635" x2="23.495" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="22.225" y1="1.27" x2="21.59" y2="0.635" width="0.2032" layer="21"/>
<wire x1="21.59" y1="-0.635" x2="22.225" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="23.495" y1="-1.27" x2="22.225" y2="-1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="5" x="10.16" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="6" x="12.7" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="7" x="15.24" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="8" x="17.78" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="9" x="20.32" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="10" x="22.86" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="14.986" y1="-0.254" x2="15.494" y2="0.254" layer="51"/>
<rectangle x1="12.446" y1="-0.254" x2="12.954" y2="0.254" layer="51"/>
<rectangle x1="9.906" y1="-0.254" x2="10.414" y2="0.254" layer="51"/>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="17.526" y1="-0.254" x2="18.034" y2="0.254" layer="51"/>
<rectangle x1="20.066" y1="-0.254" x2="20.574" y2="0.254" layer="51"/>
<rectangle x1="22.606" y1="-0.254" x2="23.114" y2="0.254" layer="51"/>
</package>
<package name="1X10_LOCK_LONGPADS">
<wire x1="1.524" y1="0" x2="1.016" y2="0" width="0.2032" layer="21"/>
<wire x1="4.064" y1="0" x2="3.556" y2="0" width="0.2032" layer="21"/>
<wire x1="6.604" y1="0" x2="6.096" y2="0" width="0.2032" layer="21"/>
<wire x1="9.144" y1="0" x2="8.636" y2="0" width="0.2032" layer="21"/>
<wire x1="11.684" y1="0" x2="11.176" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.016" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="0.9906" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.9906" x2="-0.9906" y2="1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="-0.9906" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.9906" x2="-0.9906" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="14.224" y1="0" x2="13.716" y2="0" width="0.2032" layer="21"/>
<wire x1="16.764" y1="0" x2="16.256" y2="0" width="0.2032" layer="21"/>
<wire x1="19.304" y1="0" x2="18.796" y2="0" width="0.2032" layer="21"/>
<wire x1="21.844" y1="0" x2="21.336" y2="0" width="0.2032" layer="21"/>
<wire x1="24.13" y1="0" x2="24.13" y2="-0.9906" width="0.2032" layer="21"/>
<wire x1="24.13" y1="-0.9906" x2="23.8506" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="24.13" y1="0" x2="24.13" y2="0.9906" width="0.2032" layer="21"/>
<wire x1="24.13" y1="0.9906" x2="23.8506" y2="1.27" width="0.2032" layer="21"/>
<wire x1="24.13" y1="0" x2="23.876" y2="0" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="7.62" y="-0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="10.16" y="0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="12.7" y="-0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="15.24" y="0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="17.78" y="-0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="9" x="20.32" y="0.127" drill="1.016" shape="long" rot="R90"/>
<pad name="10" x="22.86" y="-0.127" drill="1.016" shape="long" rot="R90"/>
<text x="-1.27" y="1.905" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.2921" x2="0.2921" y2="0.2921" layer="51"/>
<rectangle x1="2.2479" y1="-0.2921" x2="2.8321" y2="0.2921" layer="51"/>
<rectangle x1="4.7879" y1="-0.2921" x2="5.3721" y2="0.2921" layer="51"/>
<rectangle x1="7.3279" y1="-0.2921" x2="7.9121" y2="0.2921" layer="51" rot="R90"/>
<rectangle x1="9.8679" y1="-0.2921" x2="10.4521" y2="0.2921" layer="51"/>
<rectangle x1="12.4079" y1="-0.2921" x2="12.9921" y2="0.2921" layer="51"/>
<rectangle x1="14.9479" y1="-0.2921" x2="15.5321" y2="0.2921" layer="51"/>
<rectangle x1="17.4879" y1="-0.2921" x2="18.0721" y2="0.2921" layer="51"/>
<rectangle x1="20.0279" y1="-0.2921" x2="20.6121" y2="0.2921" layer="51"/>
<rectangle x1="22.5679" y1="-0.2921" x2="23.1521" y2="0.2921" layer="51" rot="R90"/>
</package>
<package name="1X10_SMD_COMBINED">
<wire x1="-1.37" y1="-1.25" x2="-1.37" y2="1.25" width="0.127" layer="21"/>
<wire x1="24.23" y1="1.25" x2="24.23" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-0.85" y1="-1.25" x2="-1.37" y2="-1.25" width="0.127" layer="21"/>
<wire x1="24.23" y1="-1.25" x2="23.583" y2="-1.25" width="0.127" layer="21"/>
<wire x1="23.71" y1="1.25" x2="24.23" y2="1.25" width="0.127" layer="21"/>
<wire x1="-1.37" y1="1.25" x2="-0.723" y2="1.25" width="0.127" layer="21"/>
<wire x1="14.537" y1="-1.25" x2="13.403" y2="-1.25" width="0.127" layer="21"/>
<wire x1="0.789" y1="1.25" x2="1.751" y2="1.25" width="0.127" layer="21"/>
<wire x1="3.329" y1="1.25" x2="4.291" y2="1.25" width="0.127" layer="21"/>
<wire x1="5.869" y1="1.25" x2="6.831" y2="1.25" width="0.127" layer="21"/>
<wire x1="8.409" y1="1.25" x2="9.371" y2="1.25" width="0.127" layer="21"/>
<wire x1="10.949" y1="1.25" x2="11.911" y2="1.25" width="0.127" layer="21"/>
<wire x1="13.489" y1="1.25" x2="14.451" y2="1.25" width="0.127" layer="21"/>
<wire x1="16.029" y1="1.25" x2="16.991" y2="1.25" width="0.127" layer="21"/>
<wire x1="17.077" y1="-1.25" x2="15.943" y2="-1.25" width="0.127" layer="21"/>
<wire x1="11.997" y1="-1.25" x2="10.863" y2="-1.25" width="0.127" layer="21"/>
<wire x1="9.457" y1="-1.25" x2="8.323" y2="-1.25" width="0.127" layer="21"/>
<wire x1="6.917" y1="-1.25" x2="5.783" y2="-1.25" width="0.127" layer="21"/>
<wire x1="4.377" y1="-1.25" x2="3.243" y2="-1.25" width="0.127" layer="21"/>
<wire x1="1.837" y1="-1.25" x2="0.703" y2="-1.25" width="0.127" layer="21"/>
<smd name="7B" x="15.24" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="5B" x="10.16" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="3B" x="5.08" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="8A" x="17.78" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="6A" x="12.7" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="4A" x="7.62" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="2A" x="2.54" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="1A" x="0" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="2B" x="2.54" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="3A" x="5.08" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="4B" x="7.62" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="5A" x="10.16" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="6B" x="12.7" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="7A" x="15.24" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="8B" x="17.78" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="1B" x="0" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<text x="0" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="0" y="-4.191" size="1.27" layer="27">&gt;VALUE</text>
<smd name="9A" x="20.32" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="10A" x="22.86" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="9B" x="20.32" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="10B" x="22.86" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<wire x1="18.569" y1="1.25" x2="19.531" y2="1.25" width="0.127" layer="21"/>
<wire x1="21.109" y1="1.25" x2="22.071" y2="1.25" width="0.127" layer="21"/>
<wire x1="19.617" y1="-1.25" x2="18.483" y2="-1.25" width="0.127" layer="21"/>
<wire x1="22.157" y1="-1.25" x2="21.023" y2="-1.25" width="0.127" layer="21"/>
</package>
<package name="1X10_SMD_MALE">
<text x="-1" y="3.321" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1" y="-4.591" size="1.27" layer="27">&gt;VALUE</text>
<wire x1="-1.27" y1="1.25" x2="-1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="24.13" y2="-1.25" width="0.127" layer="51"/>
<wire x1="24.13" y1="-1.25" x2="24.13" y2="1.25" width="0.127" layer="51"/>
<wire x1="24.13" y1="1.25" x2="-1.27" y2="1.25" width="0.127" layer="51"/>
<circle x="0" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="2.54" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="5.08" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="7.62" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="10.16" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="12.7" y="0" radius="0.64" width="0.127" layer="51"/>
<rectangle x1="-0.32" y1="0" x2="0.32" y2="2.75" layer="51"/>
<rectangle x1="4.76" y1="0" x2="5.4" y2="2.75" layer="51"/>
<rectangle x1="9.84" y1="0" x2="10.48" y2="2.75" layer="51"/>
<rectangle x1="2.22" y1="-2.75" x2="2.86" y2="0" layer="51" rot="R180"/>
<rectangle x1="7.3" y1="-2.75" x2="7.94" y2="0" layer="51" rot="R180"/>
<rectangle x1="12.38" y1="-2.75" x2="13.02" y2="0" layer="51" rot="R180"/>
<smd name="1" x="0" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="2" x="2.54" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="3" x="5.08" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="4" x="7.62" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="5" x="10.16" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="6" x="12.7" y="0" dx="1.02" dy="6" layer="1"/>
<wire x1="-1.27" y1="1.25" x2="-1.27" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="-1.27" y1="-1.25" x2="-0.635" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="-1.27" y1="1.25" x2="-0.635" y2="1.25" width="0.1778" layer="21"/>
<wire x1="0.762" y1="1.25" x2="1.778" y2="1.25" width="0.1778" layer="21"/>
<wire x1="3.302" y1="1.25" x2="4.318" y2="1.25" width="0.1778" layer="21"/>
<wire x1="5.842" y1="1.25" x2="6.858" y2="1.25" width="0.1778" layer="21"/>
<wire x1="8.382" y1="1.25" x2="9.398" y2="1.25" width="0.1778" layer="21"/>
<wire x1="10.922" y1="1.25" x2="11.938" y2="1.25" width="0.1778" layer="21"/>
<wire x1="1.778" y1="-1.25" x2="0.762" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="4.318" y1="-1.25" x2="3.302" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="6.858" y1="-1.25" x2="5.842" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="9.398" y1="-1.25" x2="8.382" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="11.938" y1="-1.25" x2="10.922" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="24.13" y1="-1.25" x2="24.13" y2="1.25" width="0.1778" layer="21"/>
<circle x="15.24" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="17.78" y="0" radius="0.64" width="0.127" layer="51"/>
<rectangle x1="14.92" y1="0" x2="15.56" y2="2.75" layer="51"/>
<rectangle x1="17.46" y1="-2.75" x2="18.1" y2="0" layer="51" rot="R180"/>
<smd name="7" x="15.24" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="8" x="17.78" y="0" dx="1.02" dy="6" layer="1"/>
<wire x1="16.002" y1="1.25" x2="17.018" y2="1.25" width="0.1778" layer="21"/>
<wire x1="17.018" y1="-1.25" x2="16.002" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="24.13" y1="-1.25" x2="23.495" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="24.13" y1="1.25" x2="23.495" y2="1.25" width="0.1778" layer="21"/>
<wire x1="13.462" y1="1.25" x2="14.478" y2="1.25" width="0.1778" layer="21"/>
<wire x1="14.478" y1="-1.25" x2="13.462" y2="-1.25" width="0.1778" layer="21"/>
<smd name="9" x="20.32" y="0" dx="1.02" dy="6" layer="1"/>
<smd name="10" x="22.86" y="0" dx="1.02" dy="6" layer="1"/>
<rectangle x1="22.54" y1="-2.75" x2="23.18" y2="0" layer="51" rot="R180"/>
<rectangle x1="20" y1="0" x2="20.64" y2="2.75" layer="51"/>
<circle x="20.32" y="0" radius="0.64" width="0.127" layer="51"/>
<circle x="22.86" y="0" radius="0.64" width="0.127" layer="51"/>
<wire x1="18.542" y1="1.25" x2="19.558" y2="1.25" width="0.1778" layer="21"/>
<wire x1="21.082" y1="1.25" x2="22.098" y2="1.25" width="0.1778" layer="21"/>
<wire x1="19.558" y1="-1.25" x2="18.542" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="22.098" y1="-1.25" x2="21.082" y2="-1.25" width="0.1778" layer="21"/>
</package>
<package name="1X10_NO_SILK">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="5" x="10.16" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="6" x="12.7" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="7" x="15.24" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="8" x="17.78" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="9" x="20.32" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="10" x="22.86" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="14.986" y1="-0.254" x2="15.494" y2="0.254" layer="51"/>
<rectangle x1="12.446" y1="-0.254" x2="12.954" y2="0.254" layer="51"/>
<rectangle x1="9.906" y1="-0.254" x2="10.414" y2="0.254" layer="51"/>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="17.526" y1="-0.254" x2="18.034" y2="0.254" layer="51"/>
<rectangle x1="20.066" y1="-0.254" x2="20.574" y2="0.254" layer="51"/>
<rectangle x1="22.606" y1="-0.254" x2="23.114" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="M10">
<wire x1="6.35" y1="-20.32" x2="0" y2="-20.32" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-12.7" x2="5.08" y2="-12.7" width="0.6096" layer="94"/>
<wire x1="3.81" y1="-15.24" x2="5.08" y2="-15.24" width="0.6096" layer="94"/>
<wire x1="3.81" y1="-17.78" x2="5.08" y2="-17.78" width="0.6096" layer="94"/>
<wire x1="0" y1="7.62" x2="0" y2="-20.32" width="0.4064" layer="94"/>
<wire x1="6.35" y1="-20.32" x2="6.35" y2="7.62" width="0.4064" layer="94"/>
<wire x1="0" y1="7.62" x2="6.35" y2="7.62" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-7.62" x2="5.08" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="3.81" y1="-10.16" x2="5.08" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="3.81" y1="-5.08" x2="5.08" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="3.81" y1="-2.54" x2="5.08" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="3.81" y1="0" x2="5.08" y2="0" width="0.6096" layer="94"/>
<wire x1="3.81" y1="2.54" x2="5.08" y2="2.54" width="0.6096" layer="94"/>
<wire x1="3.81" y1="5.08" x2="5.08" y2="5.08" width="0.6096" layer="94"/>
<text x="0" y="-22.86" size="1.778" layer="96">&gt;VALUE</text>
<text x="0" y="8.89" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="10.16" y="-17.78" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="10.16" y="-15.24" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="10.16" y="-12.7" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="10.16" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="10.16" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="10.16" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="7" x="10.16" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="10.16" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="10.16" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="10" x="10.16" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="M10" prefix="JP">
<description>&lt;b&gt;Header 10&lt;/b&gt;
Standard 10-pin 0.1" header. Use with straight break away headers (SKU : PRT-00116), right angle break away headers (PRT-00553), swiss pins (PRT-00743), machine pins (PRT-00117), and female headers (PRT-00115).</description>
<gates>
<gate name="G$1" symbol="M10" x="0" y="7.62"/>
</gates>
<devices>
<device name="SILK_FEMALE_PTH" package="1X10">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-11563"/>
</technology>
</technologies>
</device>
<device name="2MM" package="1X10-2MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2MMSMD" package="1X10-2MM-SMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LOCK" package="1X10_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LOCK_LONGPADS" package="1X10_LOCK_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD_COMBO-FEMALE" package="1X10_SMD_COMBINED">
<connects>
<connect gate="G$1" pin="1" pad="1A 1B"/>
<connect gate="G$1" pin="10" pad="10A 10B"/>
<connect gate="G$1" pin="2" pad="2A 2B"/>
<connect gate="G$1" pin="3" pad="3A 3B"/>
<connect gate="G$1" pin="4" pad="4A 4B"/>
<connect gate="G$1" pin="5" pad="5A 5B"/>
<connect gate="G$1" pin="6" pad="6A 6B"/>
<connect gate="G$1" pin="7" pad="7A 7B"/>
<connect gate="G$1" pin="8" pad="8A 8B"/>
<connect gate="G$1" pin="9" pad="9A 9B"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-11219"/>
</technology>
</technologies>
</device>
<device name="SMD_MALE" package="1X10_SMD_MALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-11291"/>
</technology>
</technologies>
</device>
<device name="NO_SILK_PTH_FEMALE" package="1X10_NO_SILK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-11563"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="fuse">
<description>&lt;b&gt;Fuses and Fuse Holders&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="TR5">
<description>&lt;b&gt;FUSE&lt;/b&gt;&lt;p&gt;
Wickmann</description>
<wire x1="-2.159" y1="0" x2="2.159" y2="0" width="0.1524" layer="51"/>
<wire x1="-1.27" y1="0.381" x2="-1.27" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-1.27" y1="-0.381" x2="1.27" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="1.27" y1="0.381" x2="1.27" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="1.27" y1="0.381" x2="-1.27" y2="0.381" width="0.1524" layer="51"/>
<circle x="0" y="0" radius="4.318" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="0.8128" diameter="1.778" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="0.8128" diameter="1.778" shape="long" rot="R90"/>
<text x="-2.54" y="5.08" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-2.54" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="FUSE">
<wire x1="-3.81" y1="-0.762" x2="3.81" y2="-0.762" width="0.254" layer="94"/>
<wire x1="3.81" y1="0.762" x2="-3.81" y2="0.762" width="0.254" layer="94"/>
<wire x1="3.81" y1="-0.762" x2="3.81" y2="0.762" width="0.254" layer="94"/>
<wire x1="-3.81" y1="0.762" x2="-3.81" y2="-0.762" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.397" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-2.921" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TR5" prefix="F" uservalue="yes">
<description>&lt;b&gt;FUSE&lt;/b&gt;&lt;p&gt;
Wickmann</description>
<gates>
<gate name="1" symbol="FUSE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TR5">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="BATT" library="con-wago-500" deviceset="W237-102" device=""/>
<part name="C13" library="SparkFun-Capacitors" deviceset="CAP" device="0805" value="1uF"/>
<part name="ON/OFF" library="gen3" deviceset="SPDT-SWITCH" device=""/>
<part name="3.3V_TEST" library="gen3" deviceset="TEST_PT" device=""/>
<part name="3.3REG" library="gen3" deviceset="3.3REG1A" device="REG"/>
<part name="C7" library="SparkFun-Capacitors" deviceset="CAP" device="0805" value=".01uF"/>
<part name="C10" library="SparkFun-Capacitors" deviceset="CAP" device="1206" value="47uF"/>
<part name="R10" library="SparkFun-Passives" deviceset="RESISTOR" device="0805-RES" value="80k"/>
<part name="R16" library="SparkFun-Passives" deviceset="RESISTOR" device="0805-RES" value="20k"/>
<part name="12V_TEST" library="gen3" deviceset="TEST_PT" device=""/>
<part name="BATCLAMP1" library="gen3" deviceset="DIODE-ZENER" device="DO214AC" value="DIODE-ZENERDO214AC"/>
<part name="BATCLAMP2" library="gen3" deviceset="DIODE-ZENER" device="DO214AC" value="DIODE-ZENERDO214AC"/>
<part name="DRIB_TRAN" library="gen3" deviceset="N-MOSFET" device="DPAK"/>
<part name="DRIB" library="gen3" deviceset="JST-2" device="2MM"/>
<part name="DRIB_TEST" library="gen3" deviceset="TEST_PT" device=""/>
<part name="BATSENSE_TEST" library="gen3" deviceset="TEST_PT" device=""/>
<part name="TMP" library="SparkFun-Passives" deviceset="RESISTOR" device="0805-RES" value="0"/>
<part name="POLARITY_PROTECT" library="diode" deviceset="BAT60J" device=""/>
<part name="MOTORBOARD_HEADER1" library="SparkFun-Connectors" deviceset="M10" device="SILK_FEMALE_PTH"/>
<part name="MOTORBOARD_HEADER2" library="SparkFun-Connectors" deviceset="M10" device="SILK_FEMALE_PTH"/>
<part name="MOTORBOARD_HEADER3" library="SparkFun-Connectors" deviceset="M10" device="SILK_FEMALE_PTH"/>
<part name="MOTORBOARD_HEADER4" library="SparkFun-Connectors" deviceset="M10" device="SILK_FEMALE_PTH"/>
<<<<<<< HEAD
<part name="FUSE_MOTOR_1" library="fuse" deviceset="TR5" device=""/>
<part name="FUSE_MOTOR_2" library="fuse" deviceset="TR5" device=""/>
<part name="FUSE_MOTOR3" library="fuse" deviceset="TR5" device=""/>
<part name="FUSE_MOTOR_4" library="fuse" deviceset="TR5" device=""/>
=======
>>>>>>> origin/master
<part name="R5" library="SparkFun-Passives" deviceset="RESISTOR" device="0805-RES" value="20"/>
<part name="C3" library="SparkFun-Capacitors" deviceset="CAP" device="0805" value="4.7uF"/>
<part name="R6" library="SparkFun-Passives" deviceset="RESISTOR" device="0805-RES" value="100"/>
<part name="BB_CON" library="gen3" deviceset="JST-5" device=""/>
<<<<<<< HEAD
=======
<part name="FUSE_MOTOR_3" library="fuse" deviceset="TR5" device=""/>
<part name="FUSE_MOTOR_5" library="fuse" deviceset="TR5" device=""/>
<part name="FUSE_MOTOR_6" library="fuse" deviceset="TR5" device=""/>
<part name="FUSE_MOTOR_7" library="fuse" deviceset="TR5" device=""/>
<part name="KICKER_HEADER" library="SparkFun-Connectors" deviceset="M10" device="SILK_FEMALE_PTH"/>
<part name="FUSE_KICKER" library="fuse" deviceset="TR5" device=""/>
<part name="CHARGE_HEADER" library="SparkFun-Connectors" deviceset="M10" device="SILK_FEMALE_PTH"/>
<part name="FUSE_CHARGER" library="fuse" deviceset="TR5" device=""/>
>>>>>>> origin/master
</parts>
<sheets>
<sheet>
<plain>
<text x="152.4" y="50.8" size="1.778" layer="91" rot="R180">15v -&gt; 3v division
to measure battery voltage</text>
<text x="180.34" y="60.96" size="1.778" layer="91">max gate threshold: 2.6V. 
should turn on fine with 3.3!</text>
<<<<<<< HEAD
<text x="-22.86" y="15.24" size="1.778" layer="91">Neon Indicator light to show when
the Caps are charged and dangerous</text>
<text x="167.64" y="-2.54" size="1.778" layer="91">Breakbeam output:
=======
<text x="127" y="-7.62" size="1.778" layer="91">Breakbeam output:
>>>>>>> origin/master
1.3v drop, 100mA.
2V / 20 ohm = 100mA</text>
</plain>
<instances>
<instance part="BATT" gate="-1" x="-20.32" y="83.82"/>
<instance part="BATT" gate="-2" x="-20.32" y="73.66"/>
<instance part="C13" gate="G$1" x="76.2" y="71.12"/>
<instance part="ON/OFF" gate="G$1" x="10.16" y="83.82"/>
<instance part="3.3V_TEST" gate="G$1" x="68.58" y="81.28"/>
<instance part="3.3REG" gate="G$1" x="45.72" y="71.12" rot="MR270"/>
<instance part="C7" gate="G$1" x="88.9" y="71.12"/>
<instance part="C10" gate="G$1" x="63.5" y="71.12"/>
<instance part="R10" gate="G$1" x="147.32" y="81.28" rot="R90"/>
<instance part="R16" gate="G$1" x="147.32" y="66.04" rot="R90"/>
<instance part="12V_TEST" gate="G$1" x="30.48" y="81.28"/>
<instance part="BATCLAMP1" gate="G$1" x="134.62" y="78.74" smashed="yes" rot="R90">
<attribute name="NAME" x="131.5974" y="76.2" size="1.778" layer="95" rot="R90"/>
</instance>
<instance part="BATCLAMP2" gate="G$1" x="134.62" y="68.58" smashed="yes" rot="R90">
<attribute name="NAME" x="131.5974" y="58.42" size="1.778" layer="95" rot="R90"/>
</instance>
<instance part="DRIB_TRAN" gate="G$1" x="210.82" y="71.12"/>
<instance part="DRIB" gate="G$1" x="233.68" y="83.82"/>
<instance part="DRIB_TEST" gate="G$1" x="190.5" y="71.12"/>
<instance part="BATSENSE_TEST" gate="G$1" x="139.7" y="76.2" smashed="yes">
<attribute name="NAME" x="135.89" y="71.12" size="1.778" layer="95"/>
</instance>
<instance part="TMP" gate="G$1" x="86.36" y="55.88"/>
<instance part="POLARITY_PROTECT" gate="G$1" x="-7.62" y="83.82" smashed="yes">
<attribute name="NAME" x="-17.526" y="85.725" size="1.778" layer="95"/>
<attribute name="VALUE" x="-9.906" y="80.391" size="1.778" layer="96"/>
</instance>
<instance part="MOTORBOARD_HEADER1" gate="G$1" x="7.62" y="-15.24" rot="R180"/>
<instance part="MOTORBOARD_HEADER2" gate="G$1" x="43.18" y="-15.24" rot="R180"/>
<instance part="MOTORBOARD_HEADER3" gate="G$1" x="78.74" y="-15.24" rot="R180"/>
<instance part="MOTORBOARD_HEADER4" gate="G$1" x="114.3" y="-15.24" rot="R180"/>
<instance part="R5" gate="G$1" x="142.24" y="10.16" rot="R90"/>
<instance part="C3" gate="G$1" x="132.08" y="22.86"/>
<instance part="R6" gate="G$1" x="142.24" y="30.48"/>
<instance part="BB_CON" gate="G$1" x="162.56" y="20.32"/>
<instance part="FUSE_MOTOR_3" gate="1" x="-12.7" y="-20.32" smashed="yes">
<attribute name="NAME" x="-19.05" y="-18.923" size="1.778" layer="95"/>
<attribute name="VALUE" x="-16.51" y="-23.241" size="1.778" layer="96"/>
</instance>
<instance part="FUSE_MOTOR_5" gate="1" x="22.86" y="-20.32" smashed="yes">
<attribute name="NAME" x="16.51" y="-18.923" size="1.778" layer="95"/>
<attribute name="VALUE" x="19.05" y="-23.241" size="1.778" layer="96"/>
</instance>
<instance part="FUSE_MOTOR_6" gate="1" x="58.42" y="-20.32" smashed="yes">
<attribute name="NAME" x="52.07" y="-18.923" size="1.778" layer="95"/>
<attribute name="VALUE" x="54.61" y="-23.241" size="1.778" layer="96"/>
</instance>
<instance part="FUSE_MOTOR_7" gate="1" x="93.98" y="-20.32" smashed="yes">
<attribute name="NAME" x="87.63" y="-18.923" size="1.778" layer="95"/>
<attribute name="VALUE" x="90.17" y="-23.241" size="1.778" layer="96"/>
</instance>
<instance part="KICKER_HEADER" gate="G$1" x="78.74" y="-50.8" rot="R180"/>
<instance part="FUSE_KICKER" gate="1" x="58.42" y="-55.88" smashed="yes">
<attribute name="NAME" x="52.07" y="-54.483" size="1.778" layer="95"/>
<attribute name="VALUE" x="54.61" y="-58.801" size="1.778" layer="96"/>
</instance>
<instance part="CHARGE_HEADER" gate="G$1" x="114.3" y="-50.8" rot="R180"/>
<instance part="FUSE_CHARGER" gate="1" x="93.98" y="-55.88" smashed="yes">
<attribute name="NAME" x="87.63" y="-54.483" size="1.778" layer="95"/>
<attribute name="VALUE" x="90.17" y="-58.801" size="1.778" layer="96"/>
</instance>
<instance part="R5" gate="G$1" x="182.88" y="15.24" rot="R90"/>
<instance part="C3" gate="G$1" x="172.72" y="27.94"/>
<instance part="R6" gate="G$1" x="182.88" y="35.56"/>
<instance part="BB_CON" gate="G$1" x="203.2" y="25.4"/>
</instances>
<busses>
</busses>
<nets>
<net name="3.3V" class="0">
<segment>
<wire x1="76.2" y1="78.74" x2="88.9" y2="78.74" width="0.1524" layer="91"/>
<label x="93.98" y="78.74" size="1.778" layer="95"/>
<pinref part="C13" gate="G$1" pin="1"/>
<wire x1="76.2" y1="76.2" x2="76.2" y2="78.74" width="0.1524" layer="91"/>
<pinref part="C7" gate="G$1" pin="1"/>
<wire x1="88.9" y1="78.74" x2="88.9" y2="76.2" width="0.1524" layer="91"/>
<pinref part="3.3V_TEST" gate="G$1" pin="P$1"/>
<wire x1="76.2" y1="78.74" x2="68.58" y2="78.74" width="0.1524" layer="91"/>
<junction x="76.2" y="78.74"/>
<wire x1="63.5" y1="76.2" x2="63.5" y2="78.74" width="0.1524" layer="91"/>
<wire x1="68.58" y1="78.74" x2="63.5" y2="78.74" width="0.1524" layer="91"/>
<junction x="68.58" y="78.74"/>
<pinref part="3.3REG" gate="G$1" pin="OUT"/>
<wire x1="50.8" y1="78.74" x2="63.5" y2="78.74" width="0.1524" layer="91"/>
<junction x="63.5" y="78.74"/>
<pinref part="C10" gate="G$1" pin="1"/>
<wire x1="88.9" y1="78.74" x2="93.98" y2="78.74" width="0.1524" layer="91"/>
<junction x="88.9" y="78.74"/>
</segment>
<segment>
<pinref part="R6" gate="G$1" pin="1"/>
<pinref part="C3" gate="G$1" pin="1"/>
<<<<<<< HEAD
<wire x1="177.8" y1="35.56" x2="172.72" y2="35.56" width="0.1524" layer="91"/>
<wire x1="172.72" y1="35.56" x2="172.72" y2="33.02" width="0.1524" layer="91"/>
<wire x1="172.72" y1="35.56" x2="165.1" y2="35.56" width="0.1524" layer="91"/>
<junction x="172.72" y="35.56"/>
<label x="165.1" y="35.56" size="1.778" layer="95"/>
=======
<wire x1="137.16" y1="30.48" x2="132.08" y2="30.48" width="0.1524" layer="91"/>
<wire x1="132.08" y1="30.48" x2="132.08" y2="27.94" width="0.1524" layer="91"/>
<wire x1="132.08" y1="30.48" x2="124.46" y2="30.48" width="0.1524" layer="91"/>
<junction x="132.08" y="30.48"/>
<label x="124.46" y="30.48" size="1.778" layer="95"/>
>>>>>>> origin/master
</segment>
</net>
<net name="12VGND" class="0">
<segment>
<pinref part="BATT" gate="-2" pin="KL"/>
<wire x1="-15.24" y1="73.66" x2="20.32" y2="73.66" width="0.1524" layer="91"/>
<label x="0" y="73.66" size="1.778" layer="95"/>
<wire x1="20.32" y1="73.66" x2="20.32" y2="55.88" width="0.1524" layer="91"/>
<wire x1="63.5" y1="68.58" x2="63.5" y2="66.04" width="0.1524" layer="91"/>
<label x="76.2" y="60.96" size="1.778" layer="95"/>
<pinref part="C13" gate="G$1" pin="2"/>
<wire x1="76.2" y1="68.58" x2="76.2" y2="66.04" width="0.1524" layer="91"/>
<wire x1="76.2" y1="66.04" x2="63.5" y2="66.04" width="0.1524" layer="91"/>
<pinref part="C7" gate="G$1" pin="2"/>
<wire x1="88.9" y1="68.58" x2="88.9" y2="66.04" width="0.1524" layer="91"/>
<wire x1="76.2" y1="66.04" x2="88.9" y2="66.04" width="0.1524" layer="91"/>
<junction x="76.2" y="66.04"/>
<pinref part="C10" gate="G$1" pin="2"/>
<wire x1="20.32" y1="55.88" x2="45.72" y2="55.88" width="0.1524" layer="91"/>
<wire x1="45.72" y1="55.88" x2="76.2" y2="55.88" width="0.1524" layer="91"/>
<wire x1="76.2" y1="55.88" x2="76.2" y2="66.04" width="0.1524" layer="91"/>
<pinref part="3.3REG" gate="G$1" pin="GND"/>
<wire x1="45.72" y1="60.96" x2="45.72" y2="55.88" width="0.1524" layer="91"/>
<junction x="45.72" y="55.88"/>
<pinref part="TMP" gate="G$1" pin="1"/>
<wire x1="76.2" y1="55.88" x2="81.28" y2="55.88" width="0.1524" layer="91"/>
<junction x="76.2" y="55.88"/>
</segment>
<segment>
<wire x1="213.36" y1="66.04" x2="213.36" y2="58.42" width="0.1524" layer="91"/>
<label x="213.36" y="58.42" size="1.778" layer="95"/>
<pinref part="DRIB_TRAN" gate="G$1" pin="S"/>
</segment>
<segment>
<label x="-22.86" y="-12.7" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="7"/>
<wire x1="-2.54" y1="-12.7" x2="-5.08" y2="-12.7" width="0.1524" layer="91"/>
<junction x="-2.54" y="-12.7"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="8"/>
<wire x1="-5.08" y1="-12.7" x2="-17.78" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-15.24" x2="-5.08" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="-5.08" y1="-15.24" x2="-5.08" y2="-12.7" width="0.1524" layer="91"/>
<junction x="-5.08" y="-12.7"/>
</segment>
<segment>
<label x="12.7" y="-12.7" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="7"/>
<wire x1="33.02" y1="-12.7" x2="30.48" y2="-12.7" width="0.1524" layer="91"/>
<junction x="33.02" y="-12.7"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="8"/>
<wire x1="30.48" y1="-12.7" x2="17.78" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="33.02" y1="-15.24" x2="30.48" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-15.24" x2="30.48" y2="-12.7" width="0.1524" layer="91"/>
<junction x="30.48" y="-12.7"/>
</segment>
<segment>
<label x="48.26" y="-12.7" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="7"/>
<wire x1="68.58" y1="-12.7" x2="66.04" y2="-12.7" width="0.1524" layer="91"/>
<junction x="68.58" y="-12.7"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="8"/>
<wire x1="66.04" y1="-12.7" x2="53.34" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="68.58" y1="-15.24" x2="66.04" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="66.04" y1="-15.24" x2="66.04" y2="-12.7" width="0.1524" layer="91"/>
<junction x="66.04" y="-12.7"/>
</segment>
<segment>
<label x="83.82" y="-12.7" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="7"/>
<wire x1="104.14" y1="-12.7" x2="101.6" y2="-12.7" width="0.1524" layer="91"/>
<junction x="104.14" y="-12.7"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="8"/>
<wire x1="101.6" y1="-12.7" x2="88.9" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-15.24" x2="101.6" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-15.24" x2="101.6" y2="-12.7" width="0.1524" layer="91"/>
<junction x="101.6" y="-12.7"/>
</segment>
<segment>
<label x="48.26" y="-48.26" size="1.778" layer="95"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="7"/>
<wire x1="68.58" y1="-48.26" x2="66.04" y2="-48.26" width="0.1524" layer="91"/>
<junction x="68.58" y="-48.26"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="8"/>
<wire x1="66.04" y1="-48.26" x2="53.34" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="68.58" y1="-50.8" x2="66.04" y2="-50.8" width="0.1524" layer="91"/>
<wire x1="66.04" y1="-50.8" x2="66.04" y2="-48.26" width="0.1524" layer="91"/>
<junction x="66.04" y="-48.26"/>
</segment>
<segment>
<label x="83.82" y="-48.26" size="1.778" layer="95"/>
<pinref part="CHARGE_HEADER" gate="G$1" pin="7"/>
<wire x1="104.14" y1="-48.26" x2="101.6" y2="-48.26" width="0.1524" layer="91"/>
<junction x="104.14" y="-48.26"/>
<pinref part="CHARGE_HEADER" gate="G$1" pin="8"/>
<wire x1="101.6" y1="-48.26" x2="88.9" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-50.8" x2="101.6" y2="-50.8" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-50.8" x2="101.6" y2="-48.26" width="0.1524" layer="91"/>
<junction x="101.6" y="-48.26"/>
</segment>
</net>
<net name="BAT+" class="0">
<segment>
<pinref part="ON/OFF" gate="G$1" pin="COM"/>
<wire x1="0" y1="83.82" x2="0" y2="93.98" width="0.1524" layer="91"/>
<wire x1="0" y1="93.98" x2="22.86" y2="93.98" width="0.1524" layer="91"/>
<wire x1="22.86" y1="93.98" x2="22.86" y2="88.9" width="0.1524" layer="91"/>
<pinref part="ON/OFF" gate="G$1" pin="P1"/>
<wire x1="22.86" y1="88.9" x2="20.32" y2="88.9" width="0.1524" layer="91"/>
<label x="7.62" y="93.98" size="1.778" layer="95"/>
<pinref part="POLARITY_PROTECT" gate="G$1" pin="C"/>
<wire x1="-5.08" y1="83.82" x2="0" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="3.3REG" gate="G$1" pin="IN"/>
<pinref part="ON/OFF" gate="G$1" pin="P2"/>
<wire x1="20.32" y1="78.74" x2="30.48" y2="78.74" width="0.1524" layer="91"/>
<pinref part="12V_TEST" gate="G$1" pin="P$1"/>
<wire x1="30.48" y1="78.74" x2="40.64" y2="78.74" width="0.1524" layer="91"/>
<junction x="30.48" y="78.74"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="R16" gate="G$1" pin="1"/>
<wire x1="147.32" y1="60.96" x2="147.32" y2="58.42" width="0.1524" layer="91"/>
<label x="147.32" y="55.88" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="BATCLAMP2" gate="G$1" pin="A"/>
<wire x1="134.62" y1="66.04" x2="134.62" y2="63.5" width="0.1524" layer="91"/>
<label x="132.08" y="60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="TMP" gate="G$1" pin="2"/>
<wire x1="91.44" y1="55.88" x2="93.98" y2="55.88" width="0.1524" layer="91"/>
<label x="93.98" y="55.88" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-17.78" y1="-10.16" x2="-2.54" y2="-10.16" width="0.1524" layer="91"/>
<label x="-22.86" y="-10.16" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="6"/>
<junction x="-2.54" y="-10.16"/>
</segment>
<segment>
<wire x1="17.78" y1="-10.16" x2="30.48" y2="-10.16" width="0.1524" layer="91"/>
<label x="12.7" y="-10.16" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="6"/>
<wire x1="33.02" y1="-10.16" x2="30.48" y2="-10.16" width="0.1524" layer="91"/>
<junction x="33.02" y="-10.16"/>
</segment>
<segment>
<wire x1="53.34" y1="-10.16" x2="68.58" y2="-10.16" width="0.1524" layer="91"/>
<label x="48.26" y="-10.16" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="6"/>
<junction x="68.58" y="-10.16"/>
</segment>
<segment>
<wire x1="88.9" y1="-10.16" x2="104.14" y2="-10.16" width="0.1524" layer="91"/>
<label x="83.82" y="-10.16" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="6"/>
<junction x="104.14" y="-10.16"/>
</segment>
<segment>
<<<<<<< HEAD
<wire x1="195.58" y1="15.24" x2="187.96" y2="15.24" width="0.1524" layer="91"/>
<label x="187.96" y="15.24" size="1.778" layer="95"/>
<pinref part="BB_CON" gate="G$1" pin="P$5"/>
</segment>
<segment>
<wire x1="195.58" y1="25.4" x2="172.72" y2="25.4" width="0.1524" layer="91"/>
<pinref part="C3" gate="G$1" pin="2"/>
<wire x1="172.72" y1="25.4" x2="165.1" y2="25.4" width="0.1524" layer="91"/>
<junction x="172.72" y="25.4"/>
<label x="165.1" y="25.4" size="1.778" layer="95"/>
<pinref part="BB_CON" gate="G$1" pin="P$3"/>
</segment>
=======
<wire x1="154.94" y1="10.16" x2="147.32" y2="10.16" width="0.1524" layer="91"/>
<label x="147.32" y="10.16" size="1.778" layer="95"/>
<pinref part="BB_CON" gate="G$1" pin="P$5"/>
</segment>
<segment>
<wire x1="154.94" y1="20.32" x2="132.08" y2="20.32" width="0.1524" layer="91"/>
<pinref part="C3" gate="G$1" pin="2"/>
<wire x1="132.08" y1="20.32" x2="124.46" y2="20.32" width="0.1524" layer="91"/>
<junction x="132.08" y="20.32"/>
<label x="124.46" y="20.32" size="1.778" layer="95"/>
<pinref part="BB_CON" gate="G$1" pin="P$3"/>
</segment>
<segment>
<wire x1="53.34" y1="-45.72" x2="68.58" y2="-45.72" width="0.1524" layer="91"/>
<label x="48.26" y="-45.72" size="1.778" layer="95"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="6"/>
<junction x="68.58" y="-45.72"/>
</segment>
<segment>
<wire x1="88.9" y1="-45.72" x2="104.14" y2="-45.72" width="0.1524" layer="91"/>
<label x="83.82" y="-45.72" size="1.778" layer="95"/>
<pinref part="CHARGE_HEADER" gate="G$1" pin="6"/>
<junction x="104.14" y="-45.72"/>
</segment>
>>>>>>> origin/master
</net>
<net name="12V" class="0">
<segment>
<pinref part="R10" gate="G$1" pin="2"/>
<wire x1="147.32" y1="86.36" x2="147.32" y2="88.9" width="0.1524" layer="91"/>
<label x="147.32" y="88.9" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="213.36" y1="91.44" x2="213.36" y2="86.36" width="0.1524" layer="91"/>
<wire x1="213.36" y1="86.36" x2="228.6" y2="86.36" width="0.1524" layer="91"/>
<label x="213.36" y="91.44" size="1.778" layer="95"/>
<pinref part="DRIB" gate="G$1" pin="P$1"/>
</segment>
<segment>
<pinref part="FUSE_MOTOR_3" gate="1" pin="1"/>
<wire x1="-17.78" y1="-20.32" x2="-22.86" y2="-20.32" width="0.1524" layer="91"/>
<label x="-25.4" y="-20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FUSE_MOTOR_5" gate="1" pin="1"/>
<wire x1="17.78" y1="-20.32" x2="12.7" y2="-20.32" width="0.1524" layer="91"/>
<label x="10.16" y="-20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FUSE_MOTOR_6" gate="1" pin="1"/>
<wire x1="53.34" y1="-20.32" x2="48.26" y2="-20.32" width="0.1524" layer="91"/>
<label x="45.72" y="-20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FUSE_MOTOR_7" gate="1" pin="1"/>
<wire x1="88.9" y1="-20.32" x2="83.82" y2="-20.32" width="0.1524" layer="91"/>
<label x="81.28" y="-20.32" size="1.778" layer="95"/>
</segment>
</net>
<net name="BATSENSE" class="0">
<segment>
<pinref part="R10" gate="G$1" pin="1"/>
<pinref part="R16" gate="G$1" pin="2"/>
<wire x1="147.32" y1="71.12" x2="147.32" y2="73.66" width="0.1524" layer="91"/>
<wire x1="147.32" y1="73.66" x2="147.32" y2="76.2" width="0.1524" layer="91"/>
<wire x1="147.32" y1="73.66" x2="139.7" y2="73.66" width="0.1524" layer="91"/>
<label x="119.38" y="73.66" size="1.778" layer="95"/>
<pinref part="BATCLAMP2" gate="G$1" pin="C"/>
<wire x1="139.7" y1="73.66" x2="134.62" y2="73.66" width="0.1524" layer="91"/>
<wire x1="134.62" y1="73.66" x2="124.46" y2="73.66" width="0.1524" layer="91"/>
<wire x1="134.62" y1="71.12" x2="134.62" y2="73.66" width="0.1524" layer="91"/>
<pinref part="BATCLAMP1" gate="G$1" pin="A"/>
<wire x1="134.62" y1="76.2" x2="134.62" y2="73.66" width="0.1524" layer="91"/>
<pinref part="BATSENSE_TEST" gate="G$1" pin="P$1"/>
<junction x="139.7" y="73.66"/>
<junction x="147.32" y="73.66"/>
<junction x="134.62" y="73.66"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="BATCLAMP1" gate="G$1" pin="C"/>
<wire x1="134.62" y1="81.28" x2="134.62" y2="83.82" width="0.1524" layer="91"/>
<label x="134.62" y="83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="DRIB" class="0">
<segment>
<wire x1="205.74" y1="68.58" x2="190.5" y2="68.58" width="0.1524" layer="91"/>
<label x="172.72" y="68.58" size="1.778" layer="95"/>
<pinref part="DRIB_TRAN" gate="G$1" pin="G"/>
<pinref part="DRIB_TEST" gate="G$1" pin="P$1"/>
<wire x1="190.5" y1="68.58" x2="172.72" y2="68.58" width="0.1524" layer="91"/>
<junction x="190.5" y="68.58"/>
</segment>
</net>
<net name="TO_DRIB" class="0">
<segment>
<wire x1="228.6" y1="81.28" x2="213.36" y2="81.28" width="0.1524" layer="91"/>
<wire x1="213.36" y1="81.28" x2="213.36" y2="76.2" width="0.1524" layer="91"/>
<pinref part="DRIB_TRAN" gate="G$1" pin="D"/>
<pinref part="DRIB" gate="G$1" pin="P$2"/>
</segment>
</net>
<net name="CAP+" class="0">
<segment>
<label x="48.26" y="-43.18" size="1.778" layer="95"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="5"/>
<wire x1="68.58" y1="-43.18" x2="66.04" y2="-43.18" width="0.1524" layer="91"/>
<junction x="68.58" y="-43.18"/>
<wire x1="66.04" y1="-43.18" x2="53.34" y2="-43.18" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="83.82" y="-43.18" size="1.778" layer="95"/>
<pinref part="CHARGE_HEADER" gate="G$1" pin="5"/>
<wire x1="104.14" y1="-43.18" x2="101.6" y2="-43.18" width="0.1524" layer="91"/>
<junction x="104.14" y="-43.18"/>
<wire x1="101.6" y1="-43.18" x2="88.9" y2="-43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="BAT+_UNPROTECTED" class="0">
<segment>
<pinref part="BATT" gate="-1" pin="KL"/>
<pinref part="POLARITY_PROTECT" gate="G$1" pin="A"/>
<wire x1="-10.16" y1="83.82" x2="-15.24" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="KICK_REF" class="0">
<segment>
<label x="-22.86" y="0" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="2"/>
<wire x1="-2.54" y1="0" x2="-17.78" y2="0" width="0.1524" layer="91"/>
<junction x="-2.54" y="0"/>
</segment>
<segment>
<label x="12.7" y="0" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="2"/>
<wire x1="33.02" y1="0" x2="17.78" y2="0" width="0.1524" layer="91"/>
<junction x="33.02" y="0"/>
</segment>
<segment>
<label x="48.26" y="0" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="2"/>
<wire x1="68.58" y1="0" x2="66.04" y2="0" width="0.1524" layer="91"/>
<junction x="68.58" y="0"/>
<wire x1="66.04" y1="0" x2="53.34" y2="0" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="83.82" y="0" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="2"/>
<wire x1="104.14" y1="0" x2="101.6" y2="0" width="0.1524" layer="91"/>
<junction x="104.14" y="0"/>
<wire x1="101.6" y1="0" x2="88.9" y2="0" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="48.26" y="-35.56" size="1.778" layer="95"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="2"/>
<wire x1="68.58" y1="-35.56" x2="66.04" y2="-35.56" width="0.1524" layer="91"/>
<junction x="68.58" y="-35.56"/>
<wire x1="66.04" y1="-35.56" x2="53.34" y2="-35.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="CHARGE_HEADER" gate="G$1" pin="2"/>
<wire x1="104.14" y1="-35.56" x2="101.6" y2="-35.56" width="0.1524" layer="91"/>
<junction x="104.14" y="-35.56"/>
</segment>
</net>
<net name="CHARGE_DONE" class="0">
<segment>
<label x="-22.86" y="-2.54" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="3"/>
<wire x1="-2.54" y1="-2.54" x2="-17.78" y2="-2.54" width="0.1524" layer="91"/>
<junction x="-2.54" y="-2.54"/>
</segment>
<segment>
<label x="12.7" y="-2.54" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="3"/>
<wire x1="33.02" y1="-2.54" x2="17.78" y2="-2.54" width="0.1524" layer="91"/>
<junction x="33.02" y="-2.54"/>
</segment>
<segment>
<label x="48.26" y="-2.54" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="3"/>
<wire x1="68.58" y1="-2.54" x2="66.04" y2="-2.54" width="0.1524" layer="91"/>
<junction x="68.58" y="-2.54"/>
<wire x1="66.04" y1="-2.54" x2="53.34" y2="-2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="83.82" y="-2.54" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="3"/>
<wire x1="104.14" y1="-2.54" x2="88.9" y2="-2.54" width="0.1524" layer="91"/>
<junction x="104.14" y="-2.54"/>
</segment>
<segment>
<label x="48.26" y="-38.1" size="1.778" layer="95"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="3"/>
<wire x1="68.58" y1="-38.1" x2="53.34" y2="-38.1" width="0.1524" layer="91"/>
<junction x="68.58" y="-38.1"/>
<label x="48.26" y="-38.1" size="1.778" layer="95"/>
</segment>
<segment>
<label x="83.82" y="-38.1" size="1.778" layer="95"/>
<pinref part="CHARGE_HEADER" gate="G$1" pin="3"/>
<wire x1="104.14" y1="-38.1" x2="88.9" y2="-38.1" width="0.1524" layer="91"/>
<junction x="104.14" y="-38.1"/>
<label x="83.82" y="-38.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="CHARGE" class="0">
<segment>
<label x="-22.86" y="-5.08" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="4"/>
<wire x1="-2.54" y1="-5.08" x2="-17.78" y2="-5.08" width="0.1524" layer="91"/>
<junction x="-2.54" y="-5.08"/>
</segment>
<segment>
<label x="12.7" y="-5.08" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="4"/>
<wire x1="33.02" y1="-5.08" x2="30.48" y2="-5.08" width="0.1524" layer="91"/>
<junction x="33.02" y="-5.08"/>
<wire x1="30.48" y1="-5.08" x2="17.78" y2="-5.08" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="48.26" y="-5.08" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="4"/>
<wire x1="68.58" y1="-5.08" x2="53.34" y2="-5.08" width="0.1524" layer="91"/>
<junction x="68.58" y="-5.08"/>
</segment>
<segment>
<label x="83.82" y="-5.08" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="4"/>
<junction x="104.14" y="-5.08"/>
<wire x1="104.14" y1="-5.08" x2="88.9" y2="-5.08" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="48.26" y="-40.64" size="1.778" layer="95"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="4"/>
<junction x="68.58" y="-40.64"/>
<wire x1="68.58" y1="-40.64" x2="53.34" y2="-40.64" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="83.82" y="-40.64" size="1.778" layer="95"/>
<pinref part="CHARGE_HEADER" gate="G$1" pin="4"/>
<junction x="104.14" y="-40.64"/>
<wire x1="104.14" y1="-40.64" x2="88.9" y2="-40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SS4" class="0">
<segment>
<label x="83.82" y="-7.62" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="5"/>
<wire x1="104.14" y1="-7.62" x2="101.6" y2="-7.62" width="0.1524" layer="91"/>
<junction x="104.14" y="-7.62"/>
<wire x1="101.6" y1="-7.62" x2="88.9" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SS1" class="0">
<segment>
<label x="-22.86" y="-7.62" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="5"/>
<wire x1="-2.54" y1="-7.62" x2="-17.78" y2="-7.62" width="0.1524" layer="91"/>
<junction x="-2.54" y="-7.62"/>
</segment>
</net>
<net name="SS2" class="0">
<segment>
<label x="12.7" y="-7.62" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="5"/>
<wire x1="33.02" y1="-7.62" x2="17.78" y2="-7.62" width="0.1524" layer="91"/>
<junction x="33.02" y="-7.62"/>
</segment>
</net>
<net name="SS3" class="0">
<segment>
<label x="48.26" y="-7.62" size="1.778" layer="95"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="5"/>
<wire x1="68.58" y1="-7.62" x2="66.04" y2="-7.62" width="0.1524" layer="91"/>
<junction x="68.58" y="-7.62"/>
<wire x1="66.04" y1="-7.62" x2="53.34" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="BB_OUT" class="0">
<segment>
<wire x1="127" y1="5.08" x2="142.24" y2="5.08" width="0.1524" layer="91"/>
<pinref part="R5" gate="G$1" pin="1"/>
<label x="127" y="5.08" size="1.778" layer="95"/>
</segment>
</net>
<net name="BB_IN" class="0">
<segment>
<wire x1="154.94" y1="25.4" x2="149.86" y2="25.4" width="0.1524" layer="91"/>
<wire x1="149.86" y1="25.4" x2="149.86" y2="38.1" width="0.1524" layer="91"/>
<wire x1="149.86" y1="38.1" x2="127" y2="38.1" width="0.1524" layer="91"/>
<label x="127" y="38.1" size="1.778" layer="95"/>
<pinref part="BB_CON" gate="G$1" pin="P$2"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="R5" gate="G$1" pin="2"/>
<wire x1="154.94" y1="15.24" x2="142.24" y2="15.24" width="0.1524" layer="91"/>
<pinref part="BB_CON" gate="G$1" pin="P$4"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="R6" gate="G$1" pin="2"/>
<wire x1="147.32" y1="30.48" x2="154.94" y2="30.48" width="0.1524" layer="91"/>
<pinref part="BB_CON" gate="G$1" pin="P$1"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="10"/>
<pinref part="FUSE_MOTOR_6" gate="1" pin="2"/>
<wire x1="68.58" y1="-20.32" x2="66.04" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="MOTORBOARD_HEADER3" gate="G$1" pin="9"/>
<wire x1="66.04" y1="-20.32" x2="63.5" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="68.58" y1="-17.78" x2="66.04" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="66.04" y1="-17.78" x2="66.04" y2="-20.32" width="0.1524" layer="91"/>
<junction x="66.04" y="-20.32"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="10"/>
<pinref part="FUSE_MOTOR_7" gate="1" pin="2"/>
<wire x1="104.14" y1="-20.32" x2="101.6" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="MOTORBOARD_HEADER4" gate="G$1" pin="9"/>
<wire x1="101.6" y1="-20.32" x2="99.06" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-17.78" x2="101.6" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-17.78" x2="101.6" y2="-20.32" width="0.1524" layer="91"/>
<junction x="101.6" y="-20.32"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="10"/>
<pinref part="FUSE_MOTOR_5" gate="1" pin="2"/>
<wire x1="33.02" y1="-20.32" x2="30.48" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="MOTORBOARD_HEADER2" gate="G$1" pin="9"/>
<wire x1="30.48" y1="-20.32" x2="27.94" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="33.02" y1="-17.78" x2="30.48" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-17.78" x2="30.48" y2="-20.32" width="0.1524" layer="91"/>
<junction x="30.48" y="-20.32"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="10"/>
<pinref part="FUSE_MOTOR_3" gate="1" pin="2"/>
<wire x1="-2.54" y1="-20.32" x2="-5.08" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="MOTORBOARD_HEADER1" gate="G$1" pin="9"/>
<wire x1="-5.08" y1="-20.32" x2="-7.62" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-17.78" x2="-5.08" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="-5.08" y1="-17.78" x2="-5.08" y2="-20.32" width="0.1524" layer="91"/>
<junction x="-5.08" y="-20.32"/>
</segment>
</net>
<net name="12V1" class="0">
<segment>
<pinref part="FUSE_KICKER" gate="1" pin="1"/>
<wire x1="53.34" y1="-55.88" x2="48.26" y2="-55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="KICKER_HEADER" gate="G$1" pin="10"/>
<pinref part="FUSE_KICKER" gate="1" pin="2"/>
<wire x1="68.58" y1="-55.88" x2="66.04" y2="-55.88" width="0.1524" layer="91"/>
<pinref part="KICKER_HEADER" gate="G$1" pin="9"/>
<wire x1="66.04" y1="-55.88" x2="63.5" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="68.58" y1="-53.34" x2="66.04" y2="-53.34" width="0.1524" layer="91"/>
<wire x1="66.04" y1="-53.34" x2="66.04" y2="-55.88" width="0.1524" layer="91"/>
<junction x="66.04" y="-55.88"/>
</segment>
</net>
<net name="12V2" class="0">
<segment>
<pinref part="FUSE_CHARGER" gate="1" pin="1"/>
<wire x1="88.9" y1="-55.88" x2="83.82" y2="-55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="CHARGE_HEADER" gate="G$1" pin="10"/>
<pinref part="FUSE_CHARGER" gate="1" pin="2"/>
<wire x1="104.14" y1="-55.88" x2="101.6" y2="-55.88" width="0.1524" layer="91"/>
<pinref part="CHARGE_HEADER" gate="G$1" pin="9"/>
<wire x1="101.6" y1="-55.88" x2="99.06" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-53.34" x2="101.6" y2="-53.34" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-53.34" x2="101.6" y2="-55.88" width="0.1524" layer="91"/>
<junction x="101.6" y="-55.88"/>
</segment>
</net>
<net name="BB_OUT" class="0">
<segment>
<wire x1="167.64" y1="10.16" x2="182.88" y2="10.16" width="0.1524" layer="91"/>
<pinref part="R5" gate="G$1" pin="1"/>
<label x="167.64" y="10.16" size="1.778" layer="95"/>
</segment>
</net>
<net name="BB_IN" class="0">
<segment>
<wire x1="195.58" y1="30.48" x2="190.5" y2="30.48" width="0.1524" layer="91"/>
<wire x1="190.5" y1="30.48" x2="190.5" y2="43.18" width="0.1524" layer="91"/>
<wire x1="190.5" y1="43.18" x2="167.64" y2="43.18" width="0.1524" layer="91"/>
<label x="167.64" y="43.18" size="1.778" layer="95"/>
<pinref part="BB_CON" gate="G$1" pin="P$2"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="R5" gate="G$1" pin="2"/>
<wire x1="195.58" y1="20.32" x2="182.88" y2="20.32" width="0.1524" layer="91"/>
<pinref part="BB_CON" gate="G$1" pin="P$4"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="R6" gate="G$1" pin="2"/>
<wire x1="187.96" y1="35.56" x2="195.58" y2="35.56" width="0.1524" layer="91"/>
<pinref part="BB_CON" gate="G$1" pin="P$1"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="108,1,88.9,78.74,3.3V,,,,,"/>
<approved hash="108,1,45.72,55.88,12VGND,,,,,"/>
<approved hash="108,1,0,83.82,BAT+,,,,,"/>
<approved hash="108,1,147.32,73.66,BATSENSE,,,,,"/>
<approved hash="108,1,134.62,73.66,BATSENSE,,,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
