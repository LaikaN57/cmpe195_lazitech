cmpe195_laztech
=======================
Spring 2016 / Fall 2016

What is this?
-----------------------------------------------------------------------------------------------------------------------------------------
LazTech is an upgrade kit for the K40 laser cutter/engraver.


How to Install LazTech
-----------------------------------------------------------------------------------------------------------------------------------------
This section will cover how to connect LazTech to the your computer/laptop

1. Set-up LazTech (see "How to Set-up LazTech Hardware" Section)
2. Calibrate LazTech (see "How to Calibrate LazTech Mirrors and Optical Lens Head" Section)
3. Turn on computer/laptop
4. Login as a user with sudo permission or lpadmin group member  
5. Click System Settings icon in left Menu toolbar
6. Click Printer under Hardware 
7. Click Add on the top left of Printers-localhost Window
8. Click Serial Port #1 under Device 
9. Click Forward
10. Select printer from database under Choose Driver
11. Select Generic (recommended) under Makes and click Forward
12. Select PDF under Models and click Forward
13. Rename Printer Name under Describe Printer 
14. Remove Description under Describe Printer
15. Click Apply
16. When applied, pop-window asks for test page --> Cancel
17. Close Printers-localhost Window
18. Close System Settings


How to Set-Up LazTech Hardware
-----------------------------------------------------------------------------------------------------------------------------------------
This section will cover how to set-up LazTech hardware

1. Plug cord in a wall outlet
2. Fill ¾ of a bucket with water
3. Connect a water pump to the water inlet on the back of LazTech
4. Submerge the pump in the water bucket 
5. Place water outlet from the back of LazTech into the bucket
6. Plug the pump into a wall outlet
7. Verify that water is moving through the C0  laser 
      a. C0  laser is located in the back of the machine
8. Verify that water is circulating inside the bucket
9. Plug fan into the wall outlet 
10. Place material in grid
11. Put on protective gear on
12. Plug in 110V Input Fuse 
13. Plug USB cable from computer/laptop to LazTech 
13. Turn laser on 
14. Calibrate to start point (See “How to Calibrate LazTech Mirrors and Optical Lens Head” Section)


How to Execute on LazTech 
-----------------------------------------------------------------------------------------------------------------------------------------
This section will cover how LazTech will execute on material  

1. Open LazTech cover
2. Place material in the grid of LazTech
3. Verify that material meets LazTech standards (See “Design Rules” Section)
4. Close LazTech cover
5. Open any vector-graphic application 
6. Create/Open design document
7. Verify that deisgn meets LazTech standards (See “Design Rules” Section)
8. Select File --> Print 
9. Select LazTech Printer 
10. Click Print
11. LazTech will begin executing 
12. Wait for execution to complete
13. Turn laser off 
14. Open LazTech cover and remove completed prototype


How to Calibrate LazTech Mirrors and Optical Lens Head
-----------------------------------------------------------------------------------------------------------------------------------------
This section will cover how calibrate LazTech mirrrors and optical lens head. There are two mirrors (Mirror 1 and Mirror 2) and one optical lens head that requires calibration before executing for the laser beam to precisely hit the target.

1. Make sure the laser is disabled
2. Open LazTech cover
3. Place sticky note on Mirror 2 to test Mirror 2
4. Fire laser for 1 sec
5. Make needed adjustments to hit target
6. Repeat Steps 1-5 for Mirror 2 and optical lens head 


Deisgn Rules
-----------------------------------------------------------------------------------------------------------------------------------------
This section will cover the design rules for users to follow when starting the prototype process: picking material and designing their prototypes.

All text font is converted to path object

Material options:
      • Acrylic
      • Paper
      • Leather
      • Wood

Maximum Sheet Size: 8.5” x 11”

Stroke Width: 0.001”

Color = Action:
      • Black = Cut
      • Blue = Reference 

Action = Execution 
      • Fill = Ignored
      • Stroke = Cut
      • Stroke and File = Cut
