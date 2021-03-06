	;(defun c:LFU() (load "K:\\U14147\\TOOLS\\LSP\\GENERAL.lsp") )
;(defun c:FR() (load "K:\\U14147\\TOOLS\\LSP\\GENERAL.lsp") )
(defun c:FU() (load "K:\\U14147\\TOOLS\\LSP\\GENERAL.lsp") )
(defun c:L_fu() (load "K:\\U14147\\TOOLS\\LSP\\GENERAL.lsp") )


; SET STANDARD ENVIROMENT VARIABLE
(setvar "APERTURE" 6)
(setvar "PICKBOX" 5)
(setvar "CURSORSIZE" 10)
(setvar "OSMODE" 695)
;------ AUTO LOAD STANDARD LISP ------
;(LOAD "SCREW.LSP")
;(LOAD "HOLE.LSP")
;(LOAD "NOTES.LSP")
;(LOAD "PROPERTY.LSP")
;(LOAD "WILLYSTD.LSP")
;(LOAD "WILLY1.LSP")
;(LOAD "DDMODIFY.LSP")
;(UNDEFUN C:AV())
;34,    *print
;23,    *open



;---------------------------------------------
; ****** Zoom Lisp ******
(defun c:za() (command "zoom" "all" ) )
(defun c:zx() (command "zoom" "_p" ) )
(defun c:zw() (command "zoom" "_w" ) )
(defun c:zp() (command "zoom" "_p" ) )
(defun c:ze() (command "zoom" "_e" ) )
(defun c:zi() (command "zoom" "1.2x" ) )
(defun c:zo() (command "zoom" ".833333x" ) )
(defun c:zd() (command "zoom" "2x" ) )
(defun c:zs() (command "zoom" ".35x" ) )
(defun c:CX() (command "CIRCLE" PAUSE "D" ) )

;(defun c:'ze() (command " 'zoom" "_e" ) )
;-------------------------------------

(defun c:edlfu() (command "edit" "K:\\U14147\\TOOLS\\LSP\\GENERAL.lsp") )
(defun c:edPGP() (command "edit" "acad.pgp") )


;(defun c:OP() (command "OPEN" ) )
;(defun c:C() (command "CIRCLE" ) )
(defun c:D() (command "DIST" ) )
(defun c:SR() (command "LTSCALE" ) )
(defun c:WS() (command "MOVE" ) )
(defun c:WSS() (command "MOVE" "P" "" ) )
(defun c:RTT() (command "ROTATE" "P" "" ) )
(defun c:DIC() (command "DIM" "CEN" ) )
(defun c:ESS() (command "ERASE" "P" "" ) )
(defun c:WW() (command "COPY" ) )
(defun c:WWS() (command "COPY" "P" "" ) )
;(defun c:34() (command "PRINT" ) )
(defun c:RT() (command "ROTATE" ) )
(defun c:SQ() (command "LINE" ) )
(defun c:EF() (command "EXPLODE" ) )




;QS ***** turn on all the layers
(defun c:QS()
	(command "layer" "on" "*" "")
	(command "layer" "off" "0paperf" "")
)





;             *******************
;             *   WILLY1 LSP   *
;             *******************   4/22'03
;*********************************************************************************** 
-------------------------------------------- 
;M3 ***** note for m3 thru.
      
      (defun c:M3()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq x (strcat e1 "-M3 Thru."))
	    (IF (= e1 "1")             
	       (setq x "M3 Thru.") 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------     
;M4 ***** note for m4 thru.
      
      (defun c:M4()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq x (strcat e1 "-M4 Thru."))
	    (IF (= e1 "1")             
	       (setq x "M4 Thru.") 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;M5 ***** note for m5 thru.
      
      (defun c:M5()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLE :"))
	    (setq x (strcat e1 "-M5 Thru."))
	    (IF (= e1 "1")             
	       (setq x "M5 Thru.") 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;M6 ***** note for m6 thru.
      
      (defun c:M6()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLE :"))
	    (setq x (strcat e1 "-M6 Thru."))
	    (IF (= e1 "1")             
	       (setq x "M6 Thru.") 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;M8 ***** note for m8 thru.
      
      (defun c:M8()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLE :"))
	    (setq x (strcat e1 "-M8 Thru."))
	    (IF (= e1 "1")             
	       (setq x "M8 Thru.") 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;M10 ***** note for m10 thru.
      
      (defun c:M10()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLE :"))
	    (setq x (strcat e1 "-M10 Thru."))
	    (IF (= e1 "1")             
	       (setq x "M10 Thru.") 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;M3D ***** note for m3 with depth
      
      (defun c:M3D()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq e2 (getstring "\n INPUT DEPTH :"))
	    (setq x (strcat e1 "-M3\\PDep" e2))
	    (IF (= e1 "1")             
	       (setq x (strcat "M3 Dep" e2)) 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;M4D ***** note for m4 with depth
      
      (defun c:M4D()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq e2 (getstring "\n INPUT DEPTH :"))
	    (setq x (strcat e1 "-M4 Dep" e2))
	    (IF (= e1 "1")             
	       (setq x (strcat "M4 Dep" e2)) 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;--------------------------------------------- 
;M5D ***** note for m5 with depth
      
      (defun c:M5D()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq e2 (getstring "\n INPUT DEPTH :"))
	    (setq x (strcat e1 "-M5 Dep" e2))
	    (IF (= e1 "1")             
	       (setq x (strcat "M5 Dep" e2)) 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;--------------------------------------------- 
;M6D ***** note for m6 with depth
      
      (defun c:M6D()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq e2 (getstring "\n INPUT DEPTH :"))
	    (setq x (strcat e1 "-M6 Dep" e2))
	    (IF (= e1 "1")             
	       (setq x (strcat "M6 Dep" e2)) 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;M8D ***** note for m8 with depth
      
      (defun c:M8D()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq e2 (getstring "\n INPUT DEPTH :"))
	    (setq x (strcat e1 "-M8 Dep" e2))
	    (IF (= e1 "1")             
	       (setq x (strcat "M8 Dep" e2)) 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;--------------------------------------------- 
;M10D ***** note for m10 with depth
      
      (defun c:M10D()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF THREAD HOLES :"))
	    (setq e2 (getstring "\n INPUT DEPTH :"))
	    (setq x (strcat e1 "-M10 Dep" e2))
	    (IF (= e1 "1")             
	       (setq x (strcat "M10 Dep" e2)) 
	    )
	    (setvar "cmdecho" 1)           
	    (command "leader" "nearest" pause pause pause "" x "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------   
;------ LISP FOR ROYCE HUANG USED ------
(defun c:rds() 
	(command "rename" "d" "iso" "0" "") 
	(command "rename" "d" "isod1" "1" "") 
	(command "rename" "d" "isod2" "2" "") 
	(command "rename" "d" "isotu" "tu" "") 
	(command "rename" "d" "isotd" "td" "")
)
;----------------------------------------
;CAC ***** change layer 0 color to 254 *****
(defun c:CAC(/ x)
	(setvar "cmdecho" 0)
	(command "layer" "c" 254 "0" "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;WE ***** change entrity in layer 0 to target layer
;(defun c:WE(/ x)
;       (setvar "cmdecho" 0)
;       (setq mylayer (getstring "input layer name :"))
;       (setq oldla (getvar "clayer"))
;       (command "layer" "make" mylayer "")
;       (command "layer" "t" "*" "s" "0" "f" "*" "")
;       (command "chprop" "all" "" "la" mylayer "")
;       (command "layer" "t" mylayer "")
;       (setvar "cmdecho" 1)
;)
;----------------------------------------
;Wg ***** change entrity in layer 0 to target layer
(defun c:Wg(/ x)
	(setvar "cmdecho" 0)
	(setq mylayer (getstring "input layer name :"))
	(setq oldla (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(command "layer" "t" "*" "s" "line" "f" "*" "")
	(command "chprop" "all" "" "la" mylayer "")
	(command "layer" "t" mylayer "s" mylayer "")
	(setvar "cmdecho" 1)
)
;----------------------------------------
;WW ***** change entrity in old dwg to target layer
;(defun c:WW(/ x)
;       (setvar "cmdecho" 0)
;       (setq mylayer (getstring "input layer name :"))
;       (setq oldla (getvar "clayer"))
;       (command "layer" "make" mylayer "")
;       (command "layer" "t" "*" "s" "0" "f" "*" "")
;       (command "chprop" "all" "" "la" mylayer "c" "bylayer" "lt" "bylayer" "")
;       (command "layer" "t" "*" "s" "11" "f" "*" "")
;       (command "chprop" "all" "" "la" mylayer "c" 4 "lt" "dashed" "")
;       (command "layer" "t" "*" "s" "51" "f" "*" "")
;       (command "chprop" "all" "" "la" mylayer "c" 6 "lt" "center" "")
;       (command "layer" "t" "*" "s" mylayer "f" "*" "")
;       (setvar "cmdecho" 1)
;)
;---------------------------------------------
;W41 ***** focus on the layer
(defun c:W41(/ x)
	(setvar "cmdecho" 0)
	(setq mylayer (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(command "layer" "t" "*" "s" "41" "f" "*" "")
	(command "chprop" "all" "" "la" mylayer "c" 4 "lt" "dashed" "")
	(command "layer" "t" "*" "s" mylayer "f" "*" "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;W51 ***** focus on the layer
(defun c:W51(/ x)
	(setvar "cmdecho" 0)
	(setq mylayer (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(command "layer" "t" "*" "s" "51" "f" "*" "")
	(command "chprop" "all" "" "la" mylayer "c" 6 "lt" "center" "")
	(command "layer" "t" "*" "s" mylayer "f" "*" "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;A0 ***** change to layer 0 *****
(defun c:A0()
	(command "layer" "t" "0" "s" "0" "U" "0" ""))



;XS *****DRAWING A XLINE HORIZONTAL******
(defun c:XS()(command "XLINE" "H"))

;XV *****DRAWING A XLINE VERTICAL ******
(defun c:XV()(command "XLINE" "V"))




;;;;;;;;;;;;;;SCREW.LSP;;;;;;;;;;;;;;;;;;;;














;Draw a Mx front screw-hole
(defun c:screw(/ pt0 mx sizx outd ph pt1 pt2 hpi pt3 pt4 pt5 pt6)
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq oldcen (getvar "DIMCEN"))
	(setq date '(("m1" 1.  0.25) ("m1.2"  1.2  0.25) ("m1.6"  1.6  0.35)
("m1.7" 1.7  0.35)("m2"  2. 0.4) ("m2.3"  2.3  0.4) ("m2.5"  2.5  0.45)("m2.6"
2.6  0.45)  ("m3" 3. 0.5) ("m4"  4. 0.7) ("m5"  5. 0.8)("m6" 6. 1.) ("m8" 8.
1.25)("m12" 12. 1.75)("m10" 10. 1.5)("m15" 15. 1.5)("m16" 16. 2.0)
("1" 1.  0.25) ("1.2"  1.2  0.25) ("1.6"  1.6  0.35)("1.7" 1.7  
0.35)("2"  2. 0.4) ("2.3"  2.3  0.4) ("2.5"  2.5  0.45)("2.6"
2.6  0.45)  ("3" 3. 0.5) ("4"  4. 0.7) ("5"  5. 0.8)("6" 6. 1.) ("8" 8.
1.25)("12" 12. 1.75)("10" 10. 1.5)("15" 15. 1.5)("16" 16. 2.0)))
	(setq pt0 (getpoint "\nENTER CENTER POINT :"))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq outd (cadr sizx))
	(setq ph (caddr sizx))
	(setq pt1 (polar pt0  (/ pi 2 ) (-(/ outd 2))))
	(setq pt2 (polar pt0 0 (- (/ outd 2 ) (/ ph 2.))))
	(setq hpi (/ pi 2))
	(setq pt3 (polar pt0 0 (/ outd 1.5)))
	(setq pt4 (polar pt0 hpi (/ outd 1.5)))
	(setq pt5 (polar pt0 (* hpi 2) (/ outd 1.5)))
	(setq pt6 (polar pt0 (* hpi 3) (/ outd 1.5)))
	(command "circle" pt0  pt2)
	(command "LINETYPE" "s" "continuous" "")
	(command "color" "4")
	(command "arc" pt1 "c" pt0 "A" 270)
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt3 pt5 "")
	(command "line" pt4 pt6 "")
	(command "layer" "s" oldlay "")

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
;Draw a Mx side screw-hole
(defun c:screw1(/ pt0 mx angpi hpi sizx pitch pt1 pt2 pt3 pt4 pt5 pt6 
		  pt7 pt8 pt9 pt10 pt11 pt12 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq date '(("m1" 1. 0.25) ("m1.2" 1.2 0.25) ("m1.6" 1.6 0.35)
("m1.7" 1.7 0.35)("m2" 2. 0.4) ("m2.3" 2.3 0.4) ("m2.5" 2.5 0.45)("m2.6"
2.6 0.45)  ("m3" 3. 0.5) ("m4" 4. 0.7) ("m5" 5. 0.8)("m6" 6. 1.) ("m8" 8.
1.25) ("m10" 10. 1.5) ("m12" 12. 1.75) ("m16" 16. 2.0)
("1" 1. 0.25) ("1.2" 1.2 0.25) ("1.6" 1.6 0.35)
("1.7" 1.7 0.35)("2" 2. 0.4) ("2.3" 2.3 0.4) ("2.5" 2.5 0.45)("2.6"
2.6 0.45)  ("3" 3. 0.5) ("4" 4. 0.7) ("5" 5. 0.8)("6" 6. 1.) ("8" 8.
1.25) ("10" 10. 1.5) ("12" 12. 1.75) ("16" 16. 2.0)
))
	(setq pt0 (getpoint "\nENTER CENTER POINT :"))

	(setq tmp tdp)
	(prompt "\nENTER DEPTH <")
	(prin1 tdp)
	(setq tdp (getreal "> :"))
	(if (= tdp nil) (setq tdp tmp))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(if (= ang nil) (setq ang 0))
	(setq tmp ang)
	(prompt "\nENTER ROTATE ANGLE <")
	(prin1 ang)
	(setq ang (getreal "> :"))
	(if (= ang nil) (setq ang tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq angpi (* (+ ang 90) (/ pi 180)))
	(setq hpi (/ pi 2 ))
	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq m_dia (cadr sizx))
	(setq pitch (caddr sizx))
	(setq pt1 (polar pt0 (+ angpi hpi) (/ m_dia 2)))
	(setq pt3 (polar pt0 (- angpi hpi) (/ m_dia 2)))
	(setq pt2 (polar pt1 (+ angpi pi) tdp ))
	(setq pt4 (polar pt3 (+ angpi pi) tdp ))
	(setq pt5 (polar pt3 (+ angpi hpi)  (/ pitch 2)))
	(setq pt6 (polar pt1 (- angpi hpi) (/ pitch 2)))
	(setq pt8 (polar pt5 (+ angpi pi)(+ tdp pitch)))
	(setq pt9 (polar pt6 (+ angpi pi) (+ tdp pitch)))
	(setq pt10 (polar pt0 (+ angpi pi) 
	(+ tdp pitch (* (/ (- m_dia pitch) 2) 0.57735))))
;        (setq pt10 (polar pt0 (+ angpi pi) (+ tdp 1 (* 0.7265 (- (/ m_dia 2)
;pitch)))))
	(setq pt11 (polar pt0 (+ angpi 0) 3))
	(setq pt12 (polar pt10 (+ angpi pi) 3))
	(command "LINETYPE" "s" "dashed" "")
	(command "color" "4")
	(command "line" pt1 pt2 pt4 pt3 "" )
	(command "line" pt5 pt8 "" )
	(command "line" pt6 pt9 "" )
	(command "line" pt8 pt9"" )
	(command "line" pt8 pt10 pt9"" )
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt11 pt12 "")
	(command "layer" "s" oldlay "" )

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
;Draw a Mx side screw-hole
(defun c:screw2(/ pt0 angpi hpi mx sizx pitch pt1 pt2
		pt3 pt4 pt5 pt6 pt7 pt8 pt9 pt10 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq date '(("m1" 1.  0.25) ("m2" 2. 0.4) ("m3" 3. 0.5)
("m4" 4. 0.7) ("m5" 5. 0.8) ("m6" 6. 1.) ("m8" 8. 1.25) ("m10" 10. 1.5)
("m12" 12. 1.75) ("m14" 14. 2.) ("m16" 16. 2.)
("1" 1.  0.25) ("2" 2. 0.4)("2.5" 2.5 0.45) ("3" 3. 0.5)
("4" 4. 0.7) ("5" 5. 0.8) ("6" 6. 1.) ("8" 8. 1.25) ("10" 10. 1.5)
("12" 12. 1.75) ("14" 14. 2.) ("16" 16. 2.)
))
	(setq pt0 (getpoint "\nENTER CENTER POINT :"))

	(setq tmp tdp)
	(prompt "\nENTER DEPTH <")
	(prin1 tdp)
	(setq tdp (getreal "> :"))
	(if (= tdp nil) (setq tdp tmp))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(if (= ang nil) (setq ang 0))
	(setq tmp ang)
	(prompt "\nENTER ROTATE ANGLE <")
	(prin1 ang)
	(setq ang (getreal "> :"))
	(if (= ang nil) (setq ang tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq angpi (* (+ ang 90) (/ pi 180)))
	(setq hpi (/ pi 2 ))
	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq m_dia (cadr sizx))
	(setq pitch (caddr sizx))
	(setq pt1 (polar pt0 (+ angpi hpi) (/ m_dia 2)))
	(setq pt3 (polar pt0 (- angpi hpi) (/ m_dia 2)))
	(setq pt2 (polar pt1 (+ angpi pi)  tdp ))
	(setq pt4 (polar pt3 (+ angpi pi)  tdp ))
	(setq pt5 (polar pt3 (+ angpi hpi)  (/ pitch 2)))
	(setq pt6 (polar pt1 (- angpi hpi)  (/ pitch 2)))
	(setq pt7 (polar pt5 (+ angpi pi) tdp ))
	(setq pt8 (polar pt6 (+ angpi pi) tdp ))
	(setq pt9 (polar pt0 (+ angpi 0) 3 ))
	(setq pt10 (polar pt0 (+ angpi pi) (+ tdp 3)))
	(command "LINETYPE" "s" "dashed" "")
	(command "color" "4")
	(command "line" pt1 pt2 "" )
	(command "line" pt3 pt4 "" )
	(command "line" pt5 pt7 "")
	(command "line" pt6 pt8 "")
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt9 pt10 "")
	(command "layer" "s" oldlay "" )

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)


;;;;;;;;;;;;;;;;;;;;;;;;HOLE.LSP;;;;;;;;;;;;;;;;;;;;;;;;

;Draw a common hole
(defun c:hole(/ pt0 pt1 pt2 pt3 pt4 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq pt0 (getpoint "\nENTER CENTER  POINT:"))
	(setq tmp h_dia)
	(prompt "\nENTER DIAMETER <")
	(prin1 h_dia)
	(setq h_dia (getreal "> :"))
	(if (= h_dia nil) (setq h_dia tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq hpi (/ pi 2))
	(setq pt1 (polar pt0 0 (/ h_dia 1.5)))
	(setq pt2 (polar pt0 hpi (/ h_dia 1.5)))
	(setq pt3 (polar pt0 (* hpi 2) (/ h_dia 1.5)))
	(setq pt4 (polar pt0 (* hpi 3) (/ h_dia 1.5)))
	(command "circle" pt0 "d" h_dia)
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt1 pt3 "")
	(command "line" pt2 pt4 "")
	(command "layer" "s" oldlay "")

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
; ------------------------------------------
;Draw a common side hole
(defun c:hole1(/ pt0 angpi hpi pt1 pt2 pt3 pt4 pt5 pt6 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq pt0 (getpoint "\nENTER CENTER  POINT :"))

	(setq tmp tdp)
	(prompt "\nENTER THICK <")
	(prin1 tdp)
	(setq tdp (getreal "> :"))
	(if (= tdp nil) (setq tdp tmp))
	
	(setq tmp h_dia)
	(prompt "\nENTER DIAMETER <")
	(prin1 h_dia)
	(setq h_dia (getreal "> :"))
	(if (= h_dia nil) (setq h_dia tmp))
	
	(if (= ang nil) (setq ang 0))
	(setq tmp ang)
	(prompt "\nENTER ROTATE ANGLE <")
	(prin1 ang)
	(setq ang (getreal "> :"))
	(if (= ang nil) (setq ang tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq angpi (* (+ ang 90) (/ pi 180)))
	(setq hpi (/ pi 2 ))
	(setq bigdp smd)
	(setq bid (caddr sizx))
	(setq pt1 (polar pt0 (+ angpi hpi) (/ h_dia 2)))
	(setq pt3 (polar pt0 (- angpi hpi) (/ h_dia 2)))
	(setq pt2 (polar pt1 (+ angpi pi) tdp ))
	(setq pt4 (polar pt3 (+ angpi pi) tdp ))
	(setq pt5 (polar pt0 (+ angpi 0) 3))
	(setq pt6 (polar pt0 (+ angpi pi) (+ 3 tdp)))
	(setq oldceltype (getvar "CELTYPE"))
	(command "LINETYPE" "s" "dashed" "")
	(command "color" "4")
	(command "line" pt1 pt2 "")
	(command "line" pt3 pt4 "")
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt5 pt6 "")
	(command "layer" "s" oldlay "")

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
; ------------------------------------------
;Draw a Mx top hole
(defun c:Chole(/ pt0 mx sizx in out oldcen hpi pt1 pt2 pt3 pt4)
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq oldcen (getvar "DIMCEN"))
	(setq date '(("m2" 2.5 4)("m2.5" 3 5)("m3" 3.4 6.5)("m4" 4.5 8.)("m5" 5.5 9.5)
	("m6" 6.6 11.0)("m8" 9. 14.)("m10" 11. 17.5)("m12" 14. 20.)
	("m14" 16. 23.)("m16" 18. 26.)("m18" 20. 29.)
("2" 2.5 4)("2.5" 3 5)("3" 3.4 6.5)("4" 4.5 8.)("5" 5.5 9.5)
	("6" 6.6 11.0)("8" 9. 14.)("10" 11. 17.5)("12" 14. 20.)
	("14" 16. 23.)("16" 18. 26.)("18" 20. 29.)
))

	(setq pt0 (getpoint "\nENTER CENTER  POINT:"))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq in (cadr sizx))
	(setq out (caddr sizx))
	(setq hpi (/ pi 2))
	(setq pt1 (polar pt0 0 (/ out 1.5)))
	(setq pt2 (polar pt0 hpi (/ out 1.5)))
	(setq pt3 (polar pt0 (* hpi 2) (/ out 1.5)))
	(setq pt4 (polar pt0 (* hpi 3) (/ out 1.5)))
	(command "circle" pt0 "d" in)
	(command "circle" pt0 "d" out)
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt1 pt3 "")
	(command "line" pt2 pt4 "")
	(command "layer" "s" oldlay "")

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
; ------------------------------------------
;|Draw a Mx top hole
(defun c:Chole(/ pt0 mx sizx in out oldcen hpi pt1 pt2 pt3 pt4)
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq oldcen (getvar "DIMCEN"))
	(setq date '(("m2" 2.5 4)("m2.5" 3 5)("m3" 3.4 6.5)("m4" 4.5 8.)("m5" 5.5 9.5)
	("m6" 6.6 11.0)("m8" 9. 14.)("m10" 11. 17.5)("m12" 14. 20.)
	("m14" 16. 23.)("m16" 18. 26.)("18" 20. 29.)))

	(setq pt0 (getpoint "\nENTER CENTER  POINT:"))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq in (cadr sizx))
	(setq out (caddr sizx))
	(setq hpi (/ pi 2))
	(setq pt1 (polar pt0 0 (/ out 1.5)))
	(setq pt2 (polar pt0 hpi (/ out 1.5)))
	(setq pt3 (polar pt0 (* hpi 2) (/ out 1.5)))
	(setq pt4 (polar pt0 (* hpi 3) (/ out 1.5)))
	(command "circle" pt0 "d" in)
	(command "circle" pt0 "d" out)
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt1 pt3 "")
	(command "line" pt2 pt4 "")
	(command "layer" "s" oldlay "")

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
|;
; ------------------------------------------
;Draw a Mx side counter bore
(defun c:Chole1(/ pt0 bigdp angpi hpi mx sizx smd bid pt1 pe2 pt3
	       pt4 pt5 pt6 pt7 pt8 pt9 pt10 pt11 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq date '(("m2" 2.5 4) ("m2.5" 3 5) ("m3" 3.4 6.5) ("m4" 4.5 8.) ("m5" 5.5 9.5)
("m6" 6.6 11.0) ("m8" 9. 14.) ("m10" 11. 17.5) ("m12" 14. 20.) ("m14" 16. 23.)
("m16" 18. 26.) ("18" 20. 29.)
("2" 2.5 4) ("2.5" 3 5) ("3" 3.4 6.5) ("4" 4.5 8.) ("5" 5.5 9.5)
("6" 6.6 11.0) ("8" 9. 14.) ("10" 11. 17.5) ("12" 14. 20.) ("14" 16. 23.)
("16" 18. 26.) ("18" 20. 29.)
))

	(setq pt0 (getpoint "\nENTER CENTER  POINT :"))
	(setq tmp tdp)
	(prompt "\nENTER DEPTH <")
	(prin1 tdp)
	(setq tdp (getreal "> :"))
	(if (= tdp nil) (setq tdp tmp))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(if (= ang nil) (setq ang 0))
	(setq tmp ang)
	(prompt "\nENTER ROTATE ANGLE <")
	(prin1 ang)
	(setq ang (getreal "> :"))
	(if (= ang nil) (setq ang tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq angpi (* (+ ang 90) (/ pi 180)))
	(setq hpi (/ pi 2 ))
	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq smd (cadr sizx))
	(setq bigdp smd)
	(setq bid (caddr sizx))
	(setq pt1 (polar pt0 (+ angpi hpi) (/ bid 2)))
	(setq pt3 (polar pt0 (- angpi hpi) (/ bid 2)))
	(setq pt2 (polar pt1 (+ angpi pi) bigdp ))
	(setq pt4 (polar pt3 (+ angpi pi) bigdp ))
	(setq pt7 (polar pt0 (+ angpi pi ) bigdp ))
	(setq pt5 (polar pt7 (+ angpi hpi) (/ smd 2)))
	(setq pt6 (polar pt7 (- angpi hpi) (/ smd 2)))
	(setq pt8 (polar pt5 (+ angpi pi) (- tdp bigdp )))
	(setq pt9 (polar pt6 (+ angpi pi) (- tdp bigdp )))
	(setq pt10 (polar pt0 (+ angpi 0) 3))
	(setq pt11 (polar pt0 (+ angpi pi) (+ 3 tdp)))
	(command "LINETYPE" "s" "dashed" "")
	(command "color" "4")
	(command "line" pt1 pt2 pt4 pt3 "")
	(command "line" pt5 pt8 "")
	(command "line" pt6 pt9 "")
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt10 pt11 "")
	(command "layer" "s" oldlay "")

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
; ------------------------------------------
;Draw a Mx side counter sink
(defun c:Chole2(/ pt0 angpi hpi mx sizx smd bid pt1 pt2 pt3
	       pt4 pt5 pt6 pt7 pt8 pt9 pt10 pt11 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq date '(("m3" 3.4 6.0) ("m4" 4.5 8) ("m5" 5.5 9) ("m6" 6.5 11)
	   ("m8" 9. 14.) ("m10" 11. 17.5) ("m12" 14. 20.) ("m14" 16. 23.)
("3" 3.4 6.0) ("4" 4.5 8) ("5" 5.5 9) ("6" 6.5 11)
	   ("8" 9. 14.) ("10" 11. 17.5) ("12" 14. 20.) ("14" 16. 23.)
))
	(setq pt0 (getpoint "\nENTER CENTER  POINT :"))

	(setq tmp tdp)
	(prompt "\nENTER THICK <")
	(prin1 tdp)
	(setq tdp (getreal "> :"))
	(if (= tdp nil) (setq tdp tmp))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(if (= ang nil) (setq ang 0))
	(setq tmp ang)
	(prompt "\nENTER ROTATE ANGLE <")
	(prin1 ang)
	(setq ang (getreal "> :"))
	(if (= ang nil) (setq ang tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq angpi (* (+ ang 90) (/ pi 180)))
	(setq hpi (/ pi 2 ))
	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq smd (cadr sizx))
	(setq bid (caddr sizx))
	(setq pt1 (polar pt0 (+ angpi hpi) (/ bid 2)))
	(setq pt3 (polar pt0 (- angpi hpi) (/ bid 2)))
	(setq pt2 (polar pt1 (+ angpi pi) 0.5))
	(setq pt4 (polar pt3 (+ angpi pi) 0.5))
	(setq pt7 (polar pt0 (+ angpi pi) (+ 0.5(-(/ bid 2)(/ smd 2)))))
	(setq pt5 (polar pt7 (+ angpi hpi) (/ smd 2)))
	(setq pt6 (polar pt7 (- angpi hpi) (/ smd 2)))
	(setq pt8 (polar pt5 (+ angpi pi) (- tdp (+ 0.5(-(/ bid 2)(/ smd
2))))))
	(setq pt9 (polar pt6 (+ angpi pi) (- tdp (+ 0.5(-(/ bid 2)(/ smd
2))))))
	(setq pt10 (polar pt0 (+ angpi 0) 3))
	(setq pt11 (polar pt0 (+ angpi pi) (+ 3 tdp)))
	(command "LINETYPE" "s" "dashed" "")
	(command "color" "4")
	(command "line" pt1 pt2 pt4 pt3 "" )
	(command "line" pt2 pt5 "" )
	(command "line" pt4 pt6 "" )
	(command "line" pt5 pt6 "" )
	(command "line" pt5 pt8 "" )
	(command "line" pt6 pt9 "" )
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt10 pt11 "" )
	(command "layer" "s" oldlay "" )

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)
; ------------------------------------------
;Draw a PIN HOLE
(defun c:pinhole(/ pt0 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq pt0 (getpoint "\nENTER CENTER  POINT :"))
	
	(setq tmp h_dia)
	(prompt "\nENTER DIAMETER <")
	(prin1 h_dia)
	(setq h_dia (getreal "> :"))
	(if (= h_dia nil) (setq h_dia tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)
	(setq oinsname (getvar "insname"))
	(command "insert" "pinhole" pt0 h_dia "" "" )

	(setvar "insname" oinsname)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)

;;;;;;;;;;;;;;;;;;;;;;;;NOTES.LSP;;;;;;;;;;;;;;;;;;;;;;;;

;------ LISP FOR NOTES -------
;------ COPYRIGHT 1998/03/26 ------
;-------- note for c_bore of ------------------
(defun c:PH()
	(setvar "cmdecho" 1)
	
	(setq e2 (getstring "\n INPUT THE DIAMETER OF PIN HOLE :"))
	(setq e1 (getstring "\n INPUT THE NUMBER OF PIN HOLE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x e2))
	(setq x (strcat x "{\\H"))
	(setq x (strcat x (rtos (* (getvar "DIMSCALE") 1.4))))
	(setq x (strcat x ";\\S+0.01^ 0;} Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:mn()
	(graphscr)
	(setvar "cmdecho" 1)
	(setq oce (getvar "cmdecho"))
	(setq date '(("1" "0.25") ("1.2" "0.25") ("1.6" "0.35")
	("1.7" "0.35")("2" "0.4") ("2.3" "0.4") ("2.5" "0.45")("2.6" "0.45")
	("3" "0.5") ("4" "0.7") ("5" "0.8")("6" "1.0") ("8" "1.25") 
	("12" "1.75") ("10" "1.5")("15" "1.5")("16" "2.0")))
	(setq sstmp mx)
	(prompt "\nENTER Mx DIM <M")
	(prin1 mx)
	(setq mx (getstring "> :"))
	(if (= mx "") (setq mx sstmp))
	(setq sizx (assoc mx date))
	(setq ph (cadr sizx))        
	(setq e1 (getstring "\n INPUT THE NUMBER OF SCREW HOLE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "M") 
		(setq x (strcat x "\\A1;-M"))
	)
	(setq Dp (strcat " Dp" (rtos (* 3.0 (atoi mx)) 2 0)))
	(setq x (strcat (strcat (strcat (strcat x mx) "x") ph) Dp))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:mt()
	(graphscr)
	(setvar "cmdecho" 1)
	(setq oce (getvar "cmdecho"))
	(setq date '(("1" "0.25") ("1.2" "0.25") ("1.6" "0.35")
	("1.7" "0.35")("2" "0.4") ("2.3" "0.4") ("2.5" "0.45")("2.6" "0.45")
	("3" "0.5") ("4" "0.7") ("5" "0.8")("6" "1.0") ("8" "1.25") 
	("12" "1.75") ("10" "1.5")("15" "1.5")("16" "2.0")))
	(setq sstmp mx)
	(prompt "\nENTER Mx DIM <M")
	(prin1 mx)
	(setq mx (getstring "> :"))
	(if (= mx "") (setq mx sstmp))
	(setq sizx (assoc mx date))
	(setq ph (cadr sizx))        
	(setq e1 (getstring "\n INPUT THE NUMBER OF SCREW HOLE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "M") 
		(setq x (strcat x "\\A1;-M"))
	)
	(setq x (strcat (strcat (strcat (strcat x mx) "x") ph) " Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C2()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "2.5 Thru\\P\n\n\\U+22054.0 Dep2.5"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C3()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "3.4 Thru\\P\n\n\\U+22056.5 Dep3.4"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C4()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "4.5 Thru\\P\n\n\\U+22058.0 Dep4.5"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C5()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "5.5 Thru\\P\n\n\\U+22059.5 Dep5.5"))
	(command "leader" "nearest" pause pause "" x "")
)       
(defun c:C6()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "6.6 Thru\\P\n\n\\U+220511.0 Dep6.5"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C8()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "9.0 Thru\\P\n\n\\U+220514.0 Dep9.0"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C10()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "11.0 Thru\\P\n\n\\U+220517.5 Dep11.0"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H3()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "3.4 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H4()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "4.5 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H5()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "5.5 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)       
(defun c:H6()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "6.6 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H8()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "9.0 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H10()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat "\\A1;" e1))
	(if (= e1 "") (setq x "\\A1;\\U+2205") 
		(setq x (strcat x "\\A1;-\\U+2205"))
	)
	(setq x (strcat x "11.0 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
;------ DIMENSION LISP -----------------------
;TS ****** CHANGE TEXT JUSTIFY ******
(defun c:TJ()
	(graphscr)
	(setvar "cmdecho" 0)
;        (setq stmp myTEXTScale)
;        (prompt "\ninput TEXTScale :")
;        (prin1 myTEXTScale)
;        (setq myTEXTScale (getreal "> :"))
;        (if (= myTEXTscale nil) (setq myTEXTScale stmp))
	(prompt "select TEXT to be changed:")
	(setq e1 (ssget '
	  ((-4 . "<OR") (0 . "TEXT") (0 . "MTEXT") (-4 . "OR>"))))
	(setq i 0)
	(if e1 (progn
	  (repeat (sslength e1)
	       (setq e4 (entget (ssname e1 i)))
	       (setq t_high (cdr (assoc 72 e4)))
	       (setq e2 (cons 72 0))
	       (setq e5 (assoc 72 e4))
	       (setq e4 (subst e2 e5 e4))
	       (entmod e4)
	       (setq t_high (cdr (assoc 41 e4)))
	       (setq e2 (cons 41 1.0))
	       (setq e5 (assoc 41 e4))
	       (setq e4 (subst e2 e5 e4))
	       (entmod e4)

	       (setq i (1+ i))
	  )
;          (princ "\nAll selected TEXT change to TEXTHeight :")
;          (princ (cdr e2))
	))
;        (setvar "TEXTSIZE" (* 2.0 myTEXTScale))
	(princ)
)
; -------------------------------------------
;TS ****** CHANGE TEXT SCALE ******
(defun c:TS()
	(graphscr)
	(setvar "cmdecho" 0)
	(setq stmp myTEXTScale)
	(prompt "\ninput TEXTScale :")
	(prin1 myTEXTScale)
	(setq myTEXTScale (getreal "> :"))
	(if (= myTEXTscale nil) (setq myTEXTScale stmp))
	(prompt "select TEXT to be changed:")
	(setq e1 (ssget '
	  ((-4 . "<OR") (0 . "TEXT") (0 . "MTEXT") (-4 . "OR>"))))
	(setq i 0)
	(if e1 (progn
	  (repeat (sslength e1)
	       (setq e4 (entget (ssname e1 i)))
	       (setq t_high (cdr (assoc 40 e4)))
	       (setq e2 (cons 40 (* 2.0 myTEXTScale)))
	       (setq e5 (assoc 40 e4))
	       (setq e4 (subst e2 e5 e4))
	       (entmod e4)
	       (setq i (1+ i))
	  )
	  (princ "\nAll selected TEXT change to TEXTHeight :")
	  (princ (cdr e2))
	))
	(setvar "TEXTSIZE" (* 2.0 myTEXTScale))
	(princ)
)
; --------------------------------------
;CDS ***** change DRAWING scale 
(defun c:cds()
	(graphscr)
	(setvar "cmdecho" 0)
	(setq myDWGscale (getreal "\ninput DIM SCALE :"))
	(setq new_ds (cons 40 myDWGscale))
	(setq new_dtext (cons 140 2.0))
	(setq i 0)
	(setq dt_d (tblnext "dimstyle" 1))
	(while dt_d
	  (setq dt (entget (tblobjname "dimstyle" (cdr (assoc 2 dt_d)))))
	  (setq ds (assoc 40 dt))
	  (setq dt (subst new_ds ds dt))
	  (setq ds (assoc 140 dt))
	  (setq dt (subst new_dtext ds dt))
	  (entmod dt)
	  (setq dt_d (tblnext "dimstyle"))
	)
	(setq e1 (ssget "X" '((0 . "DIMENSION"))))
	(setq i 0)
	(if e1 (progn
	  (repeat (sslength e1)
	    (setq e4 (entget (ssname e1 i)))
	    (entmod e4)
	    (setq i (1+ i))
	  ) 
	))
	(command "dimstyle" "r" (getvar "DIMSTYLE") )
	(setvar "LTSCALE" (* 2.5 myDWGscale))
	(setvar "TEXTSIZE" (* 2.0 myDWGscale))
)
;---------------------------------------------
;DI ***** change selected DIM to a identified DIMstyle 
(defun c:DI()
	(graphscr)
	(setvar "cmdecho" 0)
	(setq stmp myDIMstyle)
	(prompt "\ninput DIMSTYLE NAME :")
	(prin1 myDIMstyle)
	(setq myDIMstyle (getstring "> :"))
	(if (= myDIMstyle "") (setq myDIMstyle stmp))
	(prompt "DIM to be changed:")
	(setq e1 (ssget '((0 . "DIMENSION"))))
	(setq e2 (cons 3 myDIMstyle))
	(setq i 0)
	(if e1
	  (progn
	    (repeat (sslength e1)
		 (setq e4 (entget (ssname e1 i)))
		 (setq e5 (assoc 3 e4))
		 (setq e4 (subst e2 e5 e4))
		 (entmod e4)
		 (setq i (1+ i))
	    )
	    (princ "\nAll selected DIM change to DIMstyle :")
	    (princ (cdr e2))
	  )
	)
	(princ)
)
;---------------------------------------------
;DO ***** set dim. origin and start to dimension
(defun c:DO()
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oosmode (getvar "osmode"))
	(command "layer" "t" "dim" "on" "dim" "unlock" "dim" 
			 "s" "dim" "")
;       (setvar "dimaso" 1)
;        (setvar "osmode" 0)
;        (command "dimstyle" "r" "0")
	(prompt "Pick the Original Point")
	(command "ucs" "o" pause)
	(princ)
	(command "dimordinate" "0,0" pause)
;        (setvar "osmode" 1)
	(command "dimcontinue")
)
;DAC ***** TO ADD %%c BEFORE DIM
      (defun c:DAC() (command "dimoverride" "DIMPOST" "\\U+2205<>" "") )



;;TY ***** TO ADD TYP. AFTER DIM
      (defun c:TYP()(command "dimoverride" "DIMPOST" "<> (TYP.)" "") )
;;TY ***** TO ADD TYP. AFTER DIM
      (defun c:TY() (command "dimoverride" "DIMPOST" "<> (TYP.)" "") )


;;TR ***** TO ADD THRU. AFTER DIM
      (defun c:TR()(command "dimoverride" "DIMPOST" "<> Thru" "") )


;DF ***** TO CHANGE DIM LINEAR FACTOR
(defun c:DF() 
  (setvar "cmdecho" 0)
  (setq stmp LF)
  (prompt "\ninput DIM LINEAR FACTOR :")
  (prin1 LF)
  (setq LF (getreal "> :"))
  (if (= LF nil) (setq LF stmp))
  (command "dimoverride" "DIMLFAC" (/ 1.0 LF) "") 
)
;---------------------------------------------
CC0 ***** leader note C1  
      
      (defun c:CC0()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER :"))
	    (setq x (strcat e1 "-C0"))
	    (command "leader" "midpoint" pause pause pause x "")
)
;CC1 ***** leader note C1  
      
      (defun c:CC1()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER :"))
	    (setq x (strcat e1 "-C1"))
	    (command "leader" "midpoint" pause pause pause x "")
)
;---------------------------------------------

;---------------------------------------------
;CC2 ***** leader note C2  
      
      (defun c:CC2()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER :"))
	    (setq x (strcat e1 "-C2"))
	    (command "leader" "midpoint" pause pause pause x "")
      )
;---------------------------------------------
;CC5 ***** leader note C0.5  
      
      (defun c:CC5()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER :"))
	    (setq x (strcat e1 "-C0.5"))
	    (command "leader" pause pause pause x "")
      )

;---------------------------------------------
;BB *** PARTS NUMBER
(defun C:BB()
  (graphscr)
  (setq oce (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (if (= myDWGscale nil) (setq myDWGscale 1))
  (setq
    p1 (getpoint "\First point:")
    p2 (getpoint p1 "\Bubber center point:")
    a1 (angle p2 p1)
    p3 (polar p2 a1 (* 4.0 myDWGscale) )
    t1 (getstring "Number:")
  )
  (command "LINE" p1 p3 "")
  (command "CIRCLE" p2 (* 4.0 myDWGscale) )
  (command "TEXT" "M" p2 (* 2.0 myDWGscale) 0 t1)
; (command "DONUT" 0 1 P1 "")

  (setvar "cmdecho" oce)
  (princ)
)
;---------------------------------------------      


;----------- DRAW XLINE V-------------
(defun C:XV()
  
  (command "XLINE"  "V"))
(defun C:XZ()
  
  (command "XLINE"  "V"))
;------------- DRAW XLINE H-------------
(defun C:XS()
  
  (command "XLINE"  "H"))

(defun C:XA5()
  
  (command "XLINE"  "A" ))
;;;;;;;;;;;;;;;;;;;;;NOTES.LSP;;;;;;;;;;;;;;;;;;;;;;;;


	;------ LISP FOR LAYER MANGERMENT & PROPERTY TREATMENT ------
;------ COPYRIGHT 1998/03/26
;---------------------------------------------
;FA ***** all of layer turn on ,thaw and unlock *****
(defun c:fa()
	(command "layer" "t" "*" "on" "*" "u" "*" "")
	(command "layer" "off" "0paperf" "")
)
;---------------------------------------------
;AA***** change selected layer to match a certain entity's layer 
(defun c:AA()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities to be changed:")
	(setq
		e1 (ssget)
		e2 (entsel "\nSelect Target layer Entity")
	)
	(if (and e1 e2)
		(progn
			(setq e2 (assoc 8 (entget (car e2))))
			(setq i 0)
			(repeat (sslength e1)
				(setq e4 (entget (ssname e1 i)))
				(setq e5 (assoc 8 e4))
				(setq e4 (subst e2 e5 e4))
				(entmod e4)
				(setq i (1+ i))
			)
			(princ "\nAll selected entities change to layer ")
			(princ (cdr e2))
		)
	)
	(princ)
)
;---------------------------------------------
;AI ***** LIST LAYER *****
(defun c:AI()
	(command "layer" "?" "*" "")
)
;---------------------------------------------
;AN ***** change selected layer to a new layer 
(defun c:AN()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities to be changed:")
	(setq e1 (ssget))
	(setq mylayer (getstring "input new layer name :"))
	(setq oldla (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(setq e2 (cons 8 mylayer))
	(setq i 0)
	(repeat (sslength e1)
		 (setq e4 (entget (ssname e1 i)))
		 (setq e5 (assoc 8 e4))
		 (setq e4 (subst e2 e5 e4))
		 (entmod e4)
		 (setq i (1+ i))
	)
	(princ "\nAll selected entities change to layer ")
	(princ (cdr e2))
	(princ)
)



;AND ***** change selected layer to DIM layer 
(defun c:AND()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities to be changed:")
	(setq e1 (ssget))
	(setq mylayer "DIM")
	(setq oldla (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(setq e2 (cons 8 mylayer))
	(setq i 0)
	(repeat (sslength e1)
		 (setq e4 (entget (ssname e1 i)))
		 (setq e5 (assoc 8 e4))
		 (setq e4 (subst e2 e5 e4))
		 (entmod e4)
		 (setq i (1+ i))
	)
	(princ "\nAll selected entities change to layer ")
	(princ (cdr e2))
	(princ)
)
;---------------------------------------------
;AN1 ***** change selected layer to 1 layer 
(defun c:AN1()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities to be changed:")
	(setq e1 (ssget))
	(setq mylayer "1")
	(setq oldla (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(setq e2 (cons 8 mylayer))
	(setq i 0)
	(repeat (sslength e1)
		 (setq e4 (entget (ssname e1 i)))
		 (setq e5 (assoc 8 e4))
		 (setq e4 (subst e2 e5 e4))
		 (entmod e4)
		 (setq i (1+ i))
	)
	(princ "\nAll selected entities change to layer ")
	(princ (cdr e2))
	(princ)
)

;AN0 ***** change selected layer to 0 layer 
(defun c:AN0()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities to be changed:")
	(setq e1 (ssget))
	(setq mylayer "0")
	(setq oldla (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(setq e2 (cons 8 mylayer))
	(setq i 0)
	(repeat (sslength e1)
		 (setq e4 (entget (ssname e1 i)))
		 (setq e5 (assoc 8 e4))
		 (setq e4 (subst e2 e5 e4))
		 (entmod e4)
		 (setq i (1+ i))
	)
	(princ "\nAll selected entities change to layer ")
	(princ (cdr e2))
	(princ)
)

;AZ ***** freeze a layer
(defun c:AZ(/ x)
	(setq x (entsel "\n Select Freeze Layer:"))
	(command "layer" "freeze"   (cdr(assoc 8 (entget(car x)))) "")
)
;---------------------------------------------
;AQ ***** unlock a layer
	(defun c:AQ(/ x)
	    (setq x (entsel "\n Select Layer to be unlocked:"))
	    (command "layer" "unlock"   (cdr(assoc 8 (entget(car x)))) "")
	)
;---------------------------------------------
;AAA ***** lock a layer
	(defun c:AAA(/ x)
	    (setq x (entsel "\n Select Layer to be locked:"))
	    (command "layer" "lock"   (cdr(assoc 8 (entget(car x)))) "")
	)
;---------------------------------------------
;AD ***** turn off another layer
(defun c:AD(/ x)
	(setvar "cmdecho" 0)
	(setq x (entsel "\n Select a Layer to be view only:"))
	(command "layer" "set" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "unlock" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "off" "*" "" "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;ADD ***** turn off another layer
(defun c:ADD(/ x)
	(setvar "cmdecho" 0)
	(setq x (entsel "\n Select 1st Layer to be view :"))
	(setq xx (entsel "\n Select 2nd Layer to be view :"))
	(command "layer" "set" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "unlock" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "off" "*" "" "")
	(command "layer" "on" (cdr(assoc 8 (entget(car xx)))) "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;AF ***** focus on the layer
(defun c:AF(/ x)
	(setvar "cmdecho" 0)
	(setq x (entsel "\n Select a Layer to be focus on:"))
	(command "layer" "lock" "*" "")
	(command "layer" "unlock" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "s" (cdr(assoc 8 (entget(car x)))) "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;AW ***** focus on the layer
(defun c:AW(/ x)
	(setvar "cmdecho" 0)
	(setq x (entsel "\n Select a Layer to be focus on:"))
	(command "layer" "lock" "*" "")
	(command "layer" "unlock" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "s" (cdr(assoc 8 (entget(car x)))) "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;AC ***** change layer's color *****
(defun c:AC(/ x)
	(setvar "cmdecho" 0)
	(setq x (entsel "\n Select a Layer to be changing color:"))
	(command "layer" "c" (acad_colordlg 7) (cdr(assoc 8 (entget(car x)))) "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;ASs ***** change current layer to match an entity's layer
(defun c:ASszza(/ x)
	(setq x (entsel "\n Select object which layer is to be matched :"))
	(command "layer" "S"  (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "U"  (cdr(assoc 8 (entget(car x)))) "")
)
;---------------------------------------------
;AT ***** thaw a layer
(defun c:AT(/ x)
	(setvar "cmdecho" 0)
	(setq x (getstring "\n Input Thaw Layer Name:"))
	(command "layer" "thaw"   x "")
	(setvar "cmdecho" 1)
)

;---------------------------------------------
;ATT ***** The layers by ENTER TO THAW
(defun c:ATT(/ x)
	(setvar "cmdecho" 0)
	(setq x (getstring "\n Input Thaw Layer Name:"))
	(setq x (strcat x "*"))
	(command "layer" "thaw"   x "")
	(setvar "cmdecho" 1)
)


;---------------------------------------------
;AX ***** turn off a layer
(defun c:AX()
	(setq off_la (entsel "\n Select a Layer to be off:"))
	(command "layer" "off"   (cdr(assoc 8 (entget(car off_la)))) "")
)
;---------------------------------------------
;NP ***** turn on previous turn off 
(defun c:NP()
	(command "layer" "on" (cdr(assoc 8 (entget(car off_la)))) "")
)
;---------------------------------------------
;ZZ ***** freeze all the layers
(defun c:ZZ()
	(command "layer" "f" "*" "")
)
;---------------------------------------------
;CC ***** lock all the layers
(defun c:CC()
	(setq x (entsel "\n Select Layer :"))
	(command "layer" "lock" "*" "")  
	(command "layer" "unlock"   (cdr(assoc 8 (entget(car x)))) "")
)
;---------------------------------------------
;NN ***** turn on all the layers
(defun c:NN()
	(command "layer" "on" "*" "")
	(command "layer" "off" "0paperf" "")
)
;---------------------------------------------
;TT ***** thaw all the layers
(defun c:TT()
	(command "layer" "t" "*" "")
)
;---------------------------------------------
;QQ ***** unlock all the layers
(defun c:QQ()
	(command "layer" "unlock" "*" "")
)
;---------------------------------------------
;MO ***** change properties to be color to bylayer & linetype=continue
(defun c:mo()
	(ssget)
	(command "chprop" "p" "" "c" "bylayer" "lt" "bylayer" "")
)
;SW ***** change properties to be color to bylayer & linetype=continue
(defun c:SW()
	(ssget)
	(command "chprop" "p" "" "c" "bylayer" "lt" "bylayer" "")
)
;SW ***** change properties to be color=240 & linetype=continue
;(defun c:SW()
;       (ssget)
;       (command "chprop" "p" "" "c" "240" "lt" "bylayer" "")
;)
;---------------------------------------------
;MD ***** change properties to be dashed line
(defun c:md()
	(ssget)
	(command "chprop" "p" "" "c" 4 "lt" "dashed" "")
)
;---------------------------------------------
;NM ***** change properties to be dashed line
(defun c:NM()
	(ssget)
	(command "chprop" "p" "" "c" "bylayer" "lt" "dashed" "")
)
;---------------------------------------------
;MC ***** change properties to be center line
(defun c:mc()
	(ssget)
	(command "chprop" "p" "" "c" 6 "lt" "center" "")
)
;---------------------------------------------
;MG ***** change properties to be color=3
(defun c:mg()
	(ssget)
	(command "chprop" "p" "" "c" 3 "")
)
;MX ***** change properties to be color=4
(defun c:mX()
	(ssget)
	(command "chprop" "p" "" "c" "bylayer" "lt" "bylayer" "")
	(command "chprop" "p" "" "c" 4 "")
)
;---------------------------------------------
;MR ***** change properties to be color=1
(defun c:mr()
	(ssget)
	(command "chprop" "p" "" "c" 1 "")
)
;---------------------------------------------
;MP ***** change properties to be SECTION LINE
(defun c:mp()
	(ssget)
	(command "chprop" "p" "" "c" 2 "lt" "phantom" "")
)
;--------------------------------------------- 
;P4 ***** to plot a a4 dwg
      (defun c:P4()
	    (setvar "cmddia" 0)
	    (command "plot" "e" "5" "n" "n" "n" "m" "" "a4" "90" "n" "f" "0")
	    (setvar "cmddia" 1)
      )
;---------------------------------------------  
;P3 ***** to plot a a3 dwg
      (defun c:P3()
	    (setvar "cmddia" 0)
	    (command "plot" "e" "5" "n" "n" "n" "m" "" "420,297" "0" "n" "f" "0")
	    (setvar "cmddia" 1)
      )
;---------------------------------------------  
;--------------------------------------------------------------------------------------
;AS  ***Chang Layer To Current
       (defun c:AS(/ x)
	    (setq x (ssget)) 
;            (command "chprop" "p" "" "c" "bylayer"  "" ) 
	     (setq x1 (entget (ssname x 0)))
	     (setq x2 (assoc 8 x1))
	     (command "layer" "s" (cdr x2) "")  
       );end 


;---------------------------------------------

;---------------------------------------------
;DO2 ***** set dim. origin and start to dimension
(defun c:DO2()
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oosmode (getvar "osmode"))
	(command "layer" "t" "dim" "on" "dim" "unlock" "dim" 
			 "s" "dim" "")
	(setvar "dimaso" 1)
	(setvar "osmode" 161)
	(command "dimstyle" "r" "0")
	(prompt "Pick the Original Point")
	(command "ucs" "o" pause)
	(princ)
	(command "dimordinate" "0,0" pause)
	(setvar "osmode" 161)
	(command "dimstyle" "r" "2")
	(command "dimcontinue")
)
;---------------------------------------------
;DO1 ***** set dim. origin and start to dimension
(defun c:DO1()
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oosmode (getvar "osmode"))
	(command "layer" "t" "dim" "on" "dim" "unlock" "dim" 
			 "s" "dim" "")
	(setvar "dimaso" 1)
	(setvar "osmode" 161)
	(command "dimstyle" "r" "0")
	(prompt "Pick the Original Point")
	(command "ucs" "o" pause)
	(princ)
	(command "dimordinate" "0,0" pause)
	(setvar "osmode" 161)
	(command "dimstyle" "r" "1")
	(command "dimcontinue")
)

  
     

;---------------------------------------------
;Y2 ****** explore layout dwg to parts dwg

(defun c:Y2()
   (princ "\n\n")
   (setq e1 (getstring "\n\n\n INPUT THE PATH FOR BLOCKS TO BE WRITTEN : "))
   (setq x (getint "\n FROM LAYER (No) :"))
   (setq x1 (getint "\n TO LAYER (No) :"))
   (setvar "cmdecho" 0)
   (command "_filedia" "0") 
   (command "layer" "t" "*" "") 
   (setq i x)
   (repeat (+ (- x1 x) 1)
      (setq e2 (strcat e1 "\\000" (itoa i)))
      (if (> i 9)
	 (setq e2 (strcat e1 "\\00" (itoa i)))   
      )
      (if (> i 99)
	 (setq e2 (strcat e1 "\\0" (itoa i)))   
      )   
      (command "clayer" i)
      (command "layer" "f" "*" "")
      (command "select" "all" "")
      (command "wblock" e2 "" "0,0" "p" "")
      (command "oops")
      (setq i (+ 1 i))
      (command "layer" "t" i "") 
   )
   (command "_filedia" "1")
   (command "layer" "t" "*" "") 
)
;---------------------------------------------      
;Y3****** wblock a part

(defun c:Y3()
   (princ "\n\n")
   (setq e1 "H:\\SLOT\\B-LOCK\\PARTS")
   (setq i (getint "\n INPUT THE LAYER NUMBER TO BE WRITTEN :"))
      (command "layer" "t" "*" "")  
      (setq e2 (strcat e1 "\\000" (itoa i)))
      (if (> i 9)
	 (setq e2 (strcat e1 "\\00" (itoa i)))   
      )   
      (command "_filedia" "0")
      (command "clayer" i)
      (command "layer" "f" "*" "")
      (command "select" "all" "")
      (command "wblock" e2 "" "0,0" "p" "")
      (command "oops")
      (command "layer" "t" "*" "")
      (command "_filedia" "1")
)

;---------------------------------------------
;XX ***** STRUCTURE LINE OFFSET
      (defun c:XX()
	    (command "XLINE" "O" )
      )
;---------------------------------------------
;11 *****change color to 14
      
      (defun c:11()
	    (ssget)
	    (command "chprop" "p" "" "c" 245 "" )
      )

;---------------------------------------------      
;1 ***** DISPLAY VIEW 1
      
      (defun c:1()
	    (command "view" "r" 1 )
      )
;--------------------------------------------- 
;2 ***** DISPLAY VIEW 2
      
      (defun c:2()
	    (command "view" "r" 2 )
      )
;--------------------------------------------- 
;3 ***** DISPLAY VIEW 3
      
      (defun c:3()
	    (command "view" "r" 3 )
      )
;--------------------------------------------- 
;4 ***** DISPLAY VIEW 4
      
      (defun c:4()
	    (command "view" "r" 4 )
      )

;--------------------------------------------- 

V ***** set view number   
      
      (defun c:v()
	    (command "view" "w") )

;--------------------------------------------- 

;5 ***** DISPLAY VIEW 5
      
      (defun c:5()
	    (command "view" "r" 5 )
      )

;--------------------------------------------- 

;6***** DISPLAY VIEW 6
      
      (defun c:6()
	    (command "view" "r" 6)
      )
;--------------------------------------------- 


;;;;;;;;;;;;;;WILLYSTD.LSP;;;;;;;;;;;;;;;;;;;;


;             *******************
;             *   WILLYSTD LSP   *
;             *******************   4/22'98
;*********************************************************************************** 
--------------------------------------------      
;1 ***** DISPLAY VIEW 1
 ;     (UNDEFUN C:1())
      (defun c:1()
	    (command "view" "r" 1 )
      )
;--------------------------------------------- 
;2 ***** DISPLAY VIEW 2
      
      (defun c:2()
	    (command "view" "r" 2 )
      )
;--------------------------------------------- 
;3 ***** DISPLAY VIEW 3
      
      (defun c:3()
	    (command "view" "r" 3 )
      )
;--------------------------------------------- 
;4 ***** DISPLAY VIEW 4
      
      (defun c:4()
	    (command "view" "r" 4 )
      )
;--------------------------------------------- 
;A4 **** insert a4 frame

      (defun c:a4()
	    (command "insert" "d:\\users\\7330\\block\\a4seed" 1 "" 1 "" "0,0" "")
      )
;--------------------------------------------- 
;A3 **** insert a3 frame

      (defun c:a3()
	    (command "insert" "d:\\users\\7330\\block\\a3seed" 1 "" 1 "" "0,0" "") 
      )

;---------------------------------------------      
;C1 ***** chamfer c=1
      
      (defun c:C1()
	    (command "chamfer" "d" 1 1)
	    (command "chamfer")
      )
;---------------------------------------------
;C2 ***** chamfer c=2
      
      (defun c:CH2()
	    (command "chamfer" "d" 2 2)
	    (command "chamfer")
      )
;---------------------------------------------
;C05 ***** chamfer c=0.5
      
      (defun c:C05()
	    (command "chamfer" "d" 0.5 0.5)
	    (command "chamfer")
      )
;---------------------------------------------
;CF ***** chamfer c=0 

      (defun c:CF()
	    (command "chamfer" "d" 0 0)
	    (command "chamfer")
      )
;---------------------------------------------
;CV ***** change entry's layer by input 

      (defun c:CV()
	    (setvar "cmdecho" 1)
	    (ssget)
	    (command "chprop" "p" "" "la" pause "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;DS ***** change dimstyle
      (defun c:DS()
	    (setvar "cmdecho" 1)
	    (command "dimstyle" "r" pause "")
	    (setvar "cmdecho" 0)
      )
;---------------------------------------------
;GR ***** change dimstyle
      (defun c:GR()
	    (command "-group" "c")            
      )
;--------------------------------------------- 
(defun c:k() (command "zoom" "" ) )
;--------------------------------------------- 
;LP ***** lengthen a line dynamically   
      
      (defun c:LP()
	    (command "lengthen" "dy")
      )
;---------------------------------------------
;MTo ***** modify tolerance

     (defun c:MTO()
	    (prompt "\n\n\n(Select dim. to be modified)")
	    (ssget)
	  (setq tp (getreal "\nTop deviation :"))
	    (setq tm (getreal "\nLower deviation :"))
	    (setq tm (* -1 tm))           
	    (command "dimoverride" "dimtp" tp "dimtm" tm "" "p" "")
	    (command "dimoverride" "dimtol" "on" "" "P" "")
      )
;---------------------------------------------
T5 ***** modify tolerance

     (defun c:T5()
	    (prompt "\n\n\n(Select dim. to be modified)")
	    (ssget)
	  (setq tp (getreal "\nTop deviation :"))
	    (setq tm (getreal "\nLower deviation :"))
	    (setq tm (* -1 tm))           
	    (command "dimoverride" "dimtp" tp "dimtm" tm "" "p" "")
	    (command "dimoverride" "dimtol" "on" "" "P" "")
      )
;---------------------------------------------
;N0N1 ***** to override a pair of tol. of -0/-0.01
      (defun c:N0N1()
	    (command "dimoverride" "dimtp" " 0" "dimtm" "0.01" "dimtol" "on" "")
      )
;---------------------------------------------
;N0N2 ***** to override a pair of tol. of -0/-0.02
      (defun c:N0N2()
	    (command "dimoverride" "dimtp" " 0" "dimtm" "0.02" "dimtol" "on" "")
      )
;--------------------------------------------- 
;N1N2 ***** to override a pair of tol. of -0,01/-0.02
      (defun c:N1N2()
	    (command "dimoverride" "dimtp" "-0.01" "dimtm" "0.02" "dimtol" "on" "")
      )
;---------------------------------------------
;N1N3 ***** to override a pair of tol. of -0,01/-0.03
      (defun c:N1N3()
	    (command "dimoverride" "dimtp" "-0.01" "dimtm" "0.03" "dimtol" "on" "")
      )
;---------------------------------------------  
;N1P1 ***** to override a pair of tol. of +0,01/-0.01
      (defun c:N1P1()
	    (command "dimoverride" "dimtp" "0.01" "dimtm" "0.01" "dimtol" "on" "")
      )
;---------------------------------------------
;N2P2 ***** to override a pair of tol. of +0,02/-0.02
      (defun c:N2P2()
	    (command "dimoverride" "dimtp" "0.02" "dimtm" "0.02" "dimtol" "on" "")
      )

;---------------------------------------------
;N0P1 ***** to override a pair of tol. of +0,01/0
      (defun c:N0P1()
	    (command "dimoverride" "dimtp" "0.01" "dimtm" "0" "dimtol" "on" "")
      )

;---------------------------------------------
;N0P2 ***** to override a pair of tol. of +0,02/0
      (defun c:N0P2()
	    (command "dimoverride" "dimtp" "0.02" "dimtm" "0" "dimtol" "on" "")
      )
;---------------------------------------------
;| QA ***** turn off another layer
(defun c:QA(/ x)
	(setvar "cmdecho" 0)
	(setq x (entsel "\n Select a Layer to be view only:"))
	(command "layer" "set" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "unlock" (cdr(assoc 8 (entget(car x)))) "")
	(command "layer" "freeze" "*" "" "")
	(setvar "cmdecho" 1)
)|;
;--------------------------------------------------------------------------------------
;QW ***** on layers by selection;the other layers off     
;      (defun c:QW(/  x x1 x2 t nn )
;          (prompt "\n Select On Layer:")   
;          (setq x (ssget))
;          (setq i 0)
;                  (setq x1 (entget (ssname x i)))
;                  (setq x2 (assoc 8 x1))
;                  (command "layer" "off" "*" "y" )
;                  (command "on" (cdr x2))  
;                   (setq i 1)
;                   (setq t (sslength x))
;                   (setq nn (- t 1))
;                   (repeat nn  
;                     (setq x1 (entget (ssname x i)))
;                     (setq x2 (assoc 8 x1))
;                     (command  "on" (cdr x2) )
;                     (setq i (+ i 1))
;                    )
;                    (command  "" ) 
;       ) 
;--------------------------------------------------------------------------------------
P0P1 ***** to override a pair of tol. of+0.01/0
      (defun c:P0P1()
	    (command "dimoverride" "dimtp" " 0.01" "dimtm" "+0" "dimtol" "on" "")
      )
;--------------------------------------------- 
P0P2 ***** to override a pair of tol. of+0.02/0
      (defun c:P0P2()
	    (command "dimoverride" "dimtp" " 0.02" "dimtm" "+0" "dimtol" "on" "")
      )
;--------------------------------------------- 
;P1P2 ***** to override a pair of tol. of+0.02/+0.01
      (defun c:P1P2()
	    (command "dimoverride" "dimtp" "+0.02" "dimtm" "-0.01" "dimtol" "on" "")
      )
;--------------------------------------------- 
;P1P3 ***** to override a pair of tol. of+0.03/+0.01
      (defun c:P1P3()
	    (command "dimoverride" "dimtp" "+0.03" "dimtm" "-0.01" "dimtol" "on" "")
      )
;--------------------------------------------- 
;P2P6 ***** to override a pair of tol. of+0.06/+0.02
      (defun c:P2P6()
	    (command "dimoverride" "dimtp" "+0.06" "dimtm" "-0.02" "dimtol" "on" "")
      )
;--------------------------------------------- 
;P10P20 ***** to override a pair of tol. of+0.2/+0.1
      (defun c:P10P20()
	    (command "dimoverride" "dimtp" "+0.2" "dimtm" "-0.1" "dimtol" "on" "")
      )

;--------------------------------------------- 
;P5P10 ***** to override a pair of tol. of+0.1/0.05
      (defun c:P5P10()
	    (command "dimoverride" "dimtp" "+0.1" "dimtm" "-0.05" "dimtol" "on" "")
      )
;--------------------------------------------- 

;P0P5 ***** to override a pair of tol. of+0.05/0
      (defun c:P0P5()
	    (command "dimoverride" "dimtp" "+0.05" "dimtm" "0" "dimtol" "on" "")
      )
;--------------------------------------------- 
;N0P10 ***** to override a pair of tol. of+0.1/0
      (defun c:N0P10()
	    (command "dimoverride" "dimtp" "+0.1" "dimtm" "0" "dimtol" "on" "")
      )

;N10P10 ***** to override a pair of tol. of+0.1/-0.1
      (defun c:N10P10()
	    (command "dimoverride" "dimtp" "+0.1" "dimtm" "0.1" "dimtol" "on" "")
      )

;P4 ***** to plot a a4 dwg
      (defun c:P4()
	    (setvar "cmddia" 0)
	    (command "plot" "e" "5" "n" "n" "n" "m" "" "a4" "90" "n" "f" "0")
	    (setvar "cmddia" 1)
      )
;---------------------------------------------  
;P3 ***** to plot a a3 dwg
      (defun c:P3()
	    (setvar "cmddia" 0)
	    (command "plot" "e" "5" "n" "n" "n" "m" "" "420,297" "0" "n" "f" "0")
	    (setvar "cmddia" 1)
      )
;---------------------------------------------  
;RN ***** rename a layer
      (defun C:RN()
	    (command "rename" "la")
      )
;---------------------------------------------             
;SL ***** display a layer name 

      (defun C:SL()
	    (graphscr)
	    (setq e1 (entsel "\nTarget layer:"))
	    (setq e1 (assoc 8 (entget (car e1))))
	    (princ "\n")
	    (princ (cdr e1))
	    (princ)
      )
;---------------------------------------------
;SS ***** change current layer to match an entity's layer

      (defun c:SS(/ x)
	    (setq x (entsel "\n Select object which layer is to be matched :"))
	    (command "layer" "S"   (cdr(assoc 8 (entget(car x)))) "")
      )
;---------------------------------------------
;SN ***** set osnap to be end,int,cen
      (defun c:SN()
	    (setvar "osmode" 37)
      )
;---------------------------------------------
;TD ***** to override lower dev. of tol. 
      (defun c:TD()
	    (setq x (getreal "\n Input Lower deviation:"))
	    (command "dimoverride" "dimtm" x "dimtol" "on" "")
      )
;--------------------------------------------- 
;TG ***** thaw a layer

      (defun c:TG(/ x)
	    (setq x (getstring "\n Input Thaw Layer Name:"))
	    (command "layer" "t" x "on" x "")
      )
;---------------------------------------------
;TO ***** to disnable tol.
      (defun c:TO()
	    (command "dimoverride" "dimtol" "off" "")
      )
;---------------------------------------------
;UU ***** unlock a layer

      (defun c:UU(/ x)
	    (setq x (entsel "\n Select Layer to be locked:"))
	    (command "layer" "unlock"   (cdr(assoc 8 (entget(car x)))) "")
      )
;---------------------------------------------
;UI ***** dimordinate

      (defun c:UI()
	    (command "dimordinate" "_end")
      )
;---------------------------------------------
;UO ***** set dim. origin and start to dimension
(defun c:UO()
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oosmode (getvar "osmode"))
	(command "layer" "t" "dim" "on" "dim" "unlock" "dim" 
			 "s" "dim" "")
	(setvar "dimaso" 1)
	(setvar "osmode" 0)
	(command "dimstyle" "r" "0")
	(prompt "Pick the Original Point")
	(command "ucs" "o" "_end" pause)
	(princ)
	(command "dimordinate" "0,0" pause)
	(setvar "osmode" 1)
	(command "dimcontinue")
)
;---------------------------------------------
;V ***** set view number   
      
      (defun c:v()
	    (command "view" "w")
      )
;---------------------------------------------
;XX ***** STRUCTURE LINE OFFSET
      (defun c:XX()
	    (command "XLINE" "O" )
      )
;---------------------------------------------

;Y ****** explore layout dwg to parts dwg

(defun c:Y()
   (princ "\n\n")
;   (setq e1 (getstring "\n\n\n INPUT THE PATH FOR BLOCKS TO BE WRITTEN : "))
   (setq e1 "\d:\\users\\7330\\futurebus\\update1\\209")
   (setq x (getint "\n FROM LAYER (No) :"))
   (setq x1 (getint "\n TO LAYER (No) :"))
   (setq x2 (getint "\n SUBSTRACT NUMBER :"))
   (setq y (getstring "\n SUB-ASS'Y PREFIX :"))
   (setvar "cmdecho" 0)
   (command "_filedia" "0") 
   (command "layer" "t" "*" "")
   (setq i (- x x2))
   (setq d (+ 1 (- x1 x)))    
   (repeat d
      (setq e2 (strcat e1 "\\" y "0" (itoa i)))
      (if (> i 9)
	 (setq e2 (strcat e1 "\\" y (itoa i)))   
      )   
      (command "clayer" x)
      (command "layer" "f" "*" "")
      (command "select" "all" "")
      (command "wblock" e2 "" "0,0" "p" "")
      (command "oops")
      (setq i (+ 1 i))
      (setq x (+ 1 x))
      (command "layer" "t" x "") 
   )
   (command "_filedia" "1")
   (command "layer" "t" "*" "") 
)
;---------------------------------------------    
;Y1 ***** restore dimstyle "y1"   
      
      (defun c:Y1()
	    (command "dimstyle" "r" "y1" "")
      )
;---------------------------------------------
---------------------------------------------
;Y2 ****** explore layout dwg to parts dwg

(defun c:Y2()
   (princ "\n\n")
   (setq e1 (getstring "\n\n\n INPUT THE PATH FOR BLOCKS TO BE WRITTEN : "))
   (setq x (getint "\n FROM LAYER (No) :"))
   (setq x1 (getint "\n TO LAYER (No) :"))
   (setvar "cmdecho" 0)
   (command "_filedia" "0") 
   (command "layer" "t" "*" "") 
   (setq i x)
   (repeat (+ (- x1 x) 1)
      (setq e2 (strcat e1 "\\000" (itoa i)))
      (if (> i 9)
	 (setq e2 (strcat e1 "\\00" (itoa i)))   
      )   
      (command "clayer" i)
      (command "layer" "f" "*" "")
      (command "select" "all" "")
      (command "wblock" e2 "" "0,0" "p" "")
      (command "oops")
      (setq i (+ 1 i))
      (command "layer" "t" i "") 
   )
   (command "_filedia" "1")
   (command "layer" "t" "*" "") 
)
;---------------------------------------------      











;;;;;;;;;;;;;;ROYCE.LSP;;;;;;;;;;;;;;;;;;;;













; -----------------------------------------------------
; ------ AutoCad Lisp used for Royce Huang only -------
; ----------------------------------------------------- 
;PA ******  PURGE ALL  ******
(DEFUN C:PA()
	(COMMAND "PURGE" "A" "" "N")
)

;AV ***** change selected layer to current layer 
(defun c:AV()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities Layer change to current Layer")
	(prompt "\nSelect Entities:")
	(setq e1 (ssget))
	(setq mylayer (getvar "clayer"))
	(setq oldla (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(setq e2 (cons 8 mylayer))
	(setq i 0)
	(repeat (sslength e1)
		 (setq e4 (entget (ssname e1 i)))
		 (setq e5 (assoc 8 e4))
		 (setq e4 (subst e2 e5 e4))
		 (entmod e4)
		 (setq i (1+ i))
	)
	(princ "\nAll selected entities change to layer ")
	(princ (cdr e2))
	(princ)
)
; ---------------------------------------------------
;oe ****** OFFSET ENTITES ******
(defun c:oe()   
	(setq tmp ofds)
	(prompt "\nOffset distance <")
	(prin1 tmp)
	(setq ofds (getreal "> :"))
	(if (= ofds nil) (setq ofds tmp))
	(ssget)
	(setq pt0 (getpoint "\nPick the orignal point"))
	(setq ptd (getpoint "\nPick the offset direction"))
	(setq hpi (/ pi 2))
	(setq pt1 (polar pt0 
			(* 
				(fix 
					(+ 
						(/ (angle pt0 ptd) hpi)
					(/ pi 4))
				) 
			hpi) 
		   ofds)
	)
	(command "move" "p" "" pt0 pt1)
)
;---------------------------------------------
;cf? ****** chamfer  ******
(defun c:cf0() (command "chamfer" "d" 0 "" "chamfer") )
(defun c:cf1() (command "chamfer" "d" 1 "" "chamfer") )
(defun c:cf2() (command "chamfer" "d" 2 "" "chamfer") )
(defun c:cf5() (command "chamfer" "d" 5 "" "chamfer") )
;---------------------------------------------
;(defun c:ed1() (command "edit" "K:\\U14147\\TOOLS\\LSP\\GENERAL.lsp") )
;(defun c:ed2() (command "edit" "h:\\acad\\screw.lsp") )
;(defun c:ed3() (command "edit" "h:\\acad\\hole.lsp") )
;(defun c:ed4() (command "edit" "h:\\acad\\NOTES.LSP") )
;(defun c:ed5() (command "edit" "C:\Program Files\AutoCAD R14\PROPERTY.lsp") )
; -----------------------------------------------
(defun c:rds() 
	(command "rename" "d" "iso" "0" "") 
	(command "rename" "d" "isod1" "1" "") 
	(command "rename" "d" "isod2" "2" "") 
	(command "rename" "d" "isotu" "tu" "") 
	(command "rename" "d" "isotd" "td" "")
)
; AA ***** load acad.lsp *****
                                                                                                                                                              
;----------------------------------------
;CAC ***** change layer 0 color to 254 *****
(defun c:CAC(/ x)
	(setvar "cmdecho" 0)
	(command "layer" "c" 254 "0" "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------

;----------------------------------------
;Wg ***** change entrity in layer 0 to target layer
(defun c:Wg(/ x)
	(setvar "cmdecho" 0)
	(setq mylayer (getstring "input layer name :"))
	(setq oldla (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(command "layer" "t" "*" "s" "line" "f" "*" "")
	(command "chprop" "all" "" "la" mylayer "")
	(command "layer" "t" mylayer "s" mylayer "")
	(setvar "cmdecho" 1)
)

;---------------------------------------------
;W41 ***** focus on the layer
(defun c:W41(/ x)
	(setvar "cmdecho" 0)
	(setq mylayer (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(command "layer" "t" "*" "s" "41" "f" "*" "")
	(command "chprop" "all" "" "la" mylayer "c" 4 "lt" "dashed" "")
	(command "layer" "t" "*" "s" mylayer "f" "*" "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;W51 ***** focus on the layer
(defun c:W51(/ x)
	(setvar "cmdecho" 0)
	(setq mylayer (getvar "clayer"))
	(command "layer" "make" mylayer "")
	(command "layer" "t" "*" "s" "51" "f" "*" "")
	(command "chprop" "all" "" "la" mylayer "c" 6 "lt" "center" "")
	(command "layer" "t" "*" "s" mylayer "f" "*" "")
	(setvar "cmdecho" 1)
)
;---------------------------------------------
;A0 ***** change to layer 0 *****
(defun c:A0()
	(command "layer" "t" "0" "s" "0" "U" "0" "")
)
; ------- authorized for Royce Huang 97/5/30 -------
; BX ***** draw a box *****
(defun c:bx(/ pt0 pt1 pt2 pt3 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq pt0 (getpoint "\nENTER FIRST POINT:"))
	(setq pt1 (getpoint "\nENTER SECOND POINT:"))
	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)
	(setq pt2 (list (+ (car pt0) (car pt1)) (cadr pt0) 0 ) )
	(setq pt3 (list (car pt0) (+ (cadr pt0) (cadr pt1)) 0 ) )
	(setq pt4 (list (+ (car pt0) (car pt1)) (+ (cadr pt0) (cadr pt1)) 0 ) )
	(command "line" pt0 pt2 pt4 pt3 pt0 "")
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)







;;;;;;;;AUTO L.FU



(defun c:dx() (command "_dimordinate" ) )
(defun c:dw() (command "_dimlinear" ) )
(defun c:dc() (command "_dimbaseline") )
(defun c:sa() (command "MATCHPROP") )
;(defun c:sd() (command "md" ) )
;(defun c:sz() (command "mc" ) )
(defun c:c() (command "copy") )
(defun c:ci() (command "circle" ) )
(defun c:D() (command "DIST" ) )
;(defun c:dd() (command "ddim" ) )
;(defun c:ddd() (LOAD "DDMODIFY.LSP") (command "AI_PROPCHK" ) )
;(defun c:OP() (setvar "cmdecho" 1) (command "OPEN") )
(defun c:ep() (command "explode" ) )
;(defun c:eW() (command "exTRIM" ) )

(defun c:eT() (command "exTEND" ) )
;(defun c:w() (command "_SCREW" ) )
;(defun c:w1() (command "_SCREW1" ) )
;(defun c:w2() (command "_SCREW2" ) )
;(defun c:q() (command "_CHOLE" ) )
;(defun c:q1() (command "_CHOLE1" ) )
;(defun c:q2() (command "_CHOLE2" ) )
;(defun c:wq() (command "_hole" ) )
;(defun c:wq1() (command "_pinhole" ) )
;(defun c:wq2() (command "_hole1" ) )




;SD ***** change properties to be dashed line
(defun c:SD()
	(ssget)
	(command "chprop" "p" "" "c" 4 "lt" "dashed" "")
)
;---------------------------------------------
;NM ***** change properties to be dashed line
(defun c:NM()
	(ssget)
	(command "chprop" "p" "" "c" "bylayer" "lt" "dashed" "")
)
;---------------------------------------------
;SZ ***** change properties to be center line
(defun c:SZ()
	(ssget)
	(command "chprop" "p" "" "c" 6 "lt" "center" "")
)

;









;;;;;
Extended-TRIM - cookie-cutter routine
;
;Select a polyline, line, circle or arc and a side to trim on
;
(defun c:ew ( / dxf na p1 redraw_it)
	      (LOAD "EXTRIM.LSP")                

(if (and (not init_bonus_error) 
	 (equal -1 (load "ac_bonus.lsp"  -1)) 
    );and
    (progn (alert "Error:\n     Cannot find AC_BONUS.LSP.")(exit))
);if
(init_bonus_error (list
		   (list   "cmdecho" 0 
			 "highlight" 0
			 "regenmode" 1
			    "osmode" 0
			   "ucsicon" 0
			"offsetdist" 0
			    "attreq" 0 
			  "plinewid" 0
			 "plinetype" 1
			  "gridmode" 0
			   "celtype" "CONTINUOUS"
		   )
		   T     ;flag. True means use undo for error clean up.  
		   '(if redraw_it (redraw na 4))
		  );list  
);init_bonus_error

 ;local function
 (defun dxf (a b / ) (cdr (assoc a b)));defun

(princ "\nPick a POLYLINE, LINE, CIRCLE, or ARC for cutting edge..")
(setq na (single_select '((-4 . "<OR")
			   (0 . "CIRCLE")
			   (0 . "ARC")
			   (0 . "LINE")
			   (0 . "LWPOLYLINE")
			   (-4 . "<AND")
			    (0 . "POLYLINE")
			    (-4 . "<NOT")
			      (-4 . "&")  
			      (70 . 112)  
			    (-4 . "NOT>")
			   (-4 . "AND>")
			  (-4 . "OR>")
			 )
			 T
	 );single_select
);setq
(if na 
    (progn
     ;(setq e1 (entget na));;setq
     (redraw na 3)
     (setq redraw_it T)

     (setq p1 (getpoint "\nPick the side to trim on:"));setq
     (redraw na 4)
     (setq redraw_it nil)

     (if p1 (etrim na p1));if
    );progn
);if

(restore_old_error)
(princ)
);defun c:extrim

;;;;;;;;;;;



_dimangular
;_dimangular
; DA***** CREATES ANGULAR DIMENSION *****
;_dimangular
(defun c:DA()
	(command "_dimangular" )
)



;__dimradius

; DR***** CREATES RADIAL DIMENSION FOR CIRCLES OR ARCS *****
;__dimradius
(defun c:DR()
	(command "__dimradius" )
)



;DIMDIAMETER
; DDR***** CREATES DIAMETER DIMENSION FOR CIRCLES OR ARCS *****
;_dimdiameter
(defun c:DDR()
	(command "_dimdiameter" )
)



;_dimlinear

; DW***** CREATES LINEAR DIMENSION *****

(defun c:DW() (command "_dimlinear" ))

; DQ***** CREATES ALIGNED LINEAR DIMENSION *****

(defun c:DQ() (command "dimALIGNED" ))



;*********************************


;THAW ***** the layers by selection  thaw;  
      (defun c:THAW(/  x x1 x2 t nn )
	   (prompt "\n Select thaw Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		 ;  (command "layer" "thaw" "*"  )
		   (command "layer" "thaw" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "thaw" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 


;QZ ***** the layers by selection  thaw;  
      (defun c:QZ(/  x x1 x2 t nn )
	   (prompt "\n Select thaw Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		  (command "layer" "FREEZE" "*" )
		   ;(command "layer" "thaw" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "thaw" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 


;AQQ ***** The layers by selection  unlock    
      (defun c:AQQ(/  x x1 x2 t nn )
	   (prompt "\n Select Layers to be unlock:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		  ; (command "layer" "unlock" "*"  )
		   (command "layer" "unlock" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "unlock" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 

;UNLOCK ***** The layers by selection  unlock    
      (defun c:uNLOCK(/  x x1 x2 t nn )
	   (prompt "\n Select unlock Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		  ; (command "layer" "unlock" "*"  )
		   (command "layer" "unlock" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "unlock" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 



;LOCK ***** The layers by selection lock    
      (defun c:lock(/  x x1 x2 t nn )
	   (prompt "\n Select lock Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "lock" "*"  )
		   (command "layer" "lock" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "lock" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 

;LO(lock) ***** The layers by selection lock    
      (defun c:lo(/  x x1 x2 t nn )
	   (prompt "\n Select lock Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "lock" "*"  )
		   (command "layer" "lock" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "lock" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 
;QA(lock) ***** The layers by selection lock    
      (defun c:QA(/  x x1 x2 t nn )
	   (prompt "\n QA---The layers by selection lock. \n Select lock Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "lock" "*"  )
		   (command "layer" "lock" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "lock" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 

;ON ***** The layers by selection  on   
 
(defun c:ON()
	(command "layer" "on") )
;HN ***** The layers by ENTER TO TURN  on   
 
(defun c:HN()
	(setq tmp (getSTRING "\nENTER THE LAYER NAME TO TURN ON:"))
	;(setq tmp (strcat tmp "*"))

	(command "layer" "on" tmp  "" ) )

;HNN ***** The layers by ENTER TO TURN  on   
 
(defun c:HNN()
	(setq tmp (getSTRING "\nENTER THE LAYER NAME TO TURN ON:"))
	(setq tmp (strcat tmp "*"))

	(command "layer" "on" tmp  "" ) )

;HNN ***** The layers by ENTER TO TURN  on   
 
(defun c:QSS()
	(setq tmp (getSTRING "\nENTER THE LAYER NAME TO TURN ON:"))
	(setq tmp (strcat tmp "*"))

	(command "layer" "on" tmp  "" ) )


;HNN ***** The layers by ENTER TO TURN  on   
 
(defun c:QSA()
	(command "layer" "on" "A*" "" ) )
(defun c:QSB()
	(command "layer" "on" "B*" "" ) )
(defun c:QSC()
	(command "layer" "on" "C*" "" ) )
(defun c:QSD()
	(command "layer" "on" "D*" "" ) )
(defun c:QSE()
	(command "layer" "on" "E*" "" ) )
(defun c:QSF()
	(command "layer" "on" "F*" "" ) )
(defun c:QSG()
	(command "layer" "on" "G*" "" ) )
(defun c:QSH()
	(command "layer" "on" "H*" "" ) )
(defun c:QSI()
	(command "layer" "on" "I*" "" ) )
(defun c:QSJ()
	(command "layer" "on" "J*" "" ) )
(defun c:QSK()
	(command "layer" "on" "K*" "" ) )
(defun c:QSL()
	(command "layer" "on" "L*" "" ) )
(defun c:QSM()
	(command "layer" "on" "M*" "" ) )
(defun c:QSN()
	(command "layer" "on" "N*" "" ) )

(defun c:WEE()
	(setq tmp (getSTRING "\nENTER THE LAYER NAME TO TURN ON:"))
	(setq tmp (strcat tmp "*"))

	(command "layer" "on" tmp  "" ) )

;oll ***** The layers by ENTER TO TURN  on (THE OTHERS OFF) 
 
(defun c:oll()
	(setq tmp (getSTRING "\nENTER THE LAYER NAME TO TURN ON (THE OTHERS OFF):"))
	(setq tmp (strcat tmp "*"))
	(command "layer" "oFF" "*" "Y" "on" tmp  "") )
	
;HMM ***** The layers by ENTER TO TURN  oFF
(defun c:HMM()
	(setq tmp (getSTRING "\nENTER THE LAYER NAME TO TURN OFF:"))
	(setq tmp (strcat tmp "*"))

	(command "layer" "oFF" tmp  "" ) )

;HJ ***** The layers by ENTER  TO VIEW ONLY  on   
 
(defun c:HJ()

(setq tmp (getSTRING "\nENTER THE LAYER NAME TO VIEW ONLY:"))
	
	(command "layer" "SET" tmp "OFF" "*"  "N" "")  )



;OFF ***** The layers by selection  OFF
      (defun c:off(/  x x1 x2 t nn )
	   (prompt "\n Select off Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		 ;  (command "layer" "off" "*" "y" )
		   (command "layer" "off" (cdr x2) )  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "off" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 

;OF ***** The layers by selection  OFF
      (defun c:of(/  x x1 x2 t nn )
	   (prompt "\n Select off Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		 ;  (command "layer" "off" "*" "y" )
		   (command "layer" "off" (cdr x2) )  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "off" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 


;       ****************************


;Freeze ***** The layers by selection  Freeze   
      (defun c:freeze(/  x x1 x2 t nn )
	   (prompt "\n Select freeze Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "thaw" "*"  )
		   (command "layer" "freeze" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "freeze" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 


;Fz  ***** The layers by selection  Freeze   
      (defun c:fZ(/  x x1 x2 t nn )
	   (prompt "\n Select freeze Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "thaw" "*"  )
		   (command "layer" "freeze" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "freeze" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 


;AZZ  ***** The layers by selection  Freeze   
      (defun c:AZZ(/  x x1 x2 t nn )
	   (prompt "\n Select freeze Layer:")   
	   (setq x (ssget))
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "thaw" "*"  )
		   (command "layer" "freeze" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "freeze" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;























;;;     BNSLAYER.LSP
;;;     Copyright (C) 1997 by Autodesk, Inc.
;;;
;;;     Created 2/21/97 by Dominic Panholzer
;;;
;;;     Permission to use, copy, modify, and distribute this software
;;;     for any purpose and without fee is hereby granted, provided
;;;     that the above copyright notice appears in all copies and 
;;;     that both that copyright notice and the limited warranty and 
;;;     restricted rights notice below appear in all supporting 
;;;     documentation.
;;;
;;;     AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.  
;;;     AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
;;;     MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
;;;     DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
;;;     UNINTERRUPTED OR ERROR FREE.
;;;
;;;     Use, duplication, or disclosure by the U.S. Government is subject to 
;;;     restrictions set forth in FAR 52.227-19 (Commercial Computer 
;;;     Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
;;;     (Rights in Technical Data and Computer Software), as applicable.
;;;
;;;  ----------------------------------------------------------------
;;;
;;;     This file contains a library of layer based routines. See individual
;;;     routines for descriptions.
;;;
;;;  External Functions:
;;;
;;;     INIT_BONUS_ERROR  --> AC_BONUS.LSP   Intializes bonus error routine
;;;     RESTORE_OLD_ERROR --> AC_BONUS.LSP   restores old error routine
;;;


; -------------------- ISOLATE LAYER FUNCTION --------------------
; Isolates selected object's layer by turning all other layers off
; ----------------------------------------------------------------

(Defun C:LAYISO (/ SS CNT LAY LAYLST VAL)

  (init_bonus_error 
   (list
    (list "cmdecho" 0
	  "expert"  0
      )
      T     ;flag. True means use undo for error clean up.  
    );list  
 );init_bonus_error

  (if (not (setq SS (ssget "i")))
    (progn
      (prompt "\nSelect object(s) on the layer(s) to be ISOLATED: ")
      (setq SS (ssget))
    )
  )

  (if SS
    (progn

      (setq CNT 0)

      (while (setq LAY (ssname SS CNT))
	(setq LAY (cdr (assoc 8 (entget LAY))))
	(if (not (member LAY LAYLST))
	  (setq LAYLST (cons LAY LAYLST))
	)
	(setq CNT (1+ CNT))
      )

      (if (member (getvar "CLAYER") LAYLST)
	(setq LAY (getvar "CLAYER"))
	(setvar "CLAYER" (setq LAY (last LAYLST)))
      )

      (command "_.-LAYER" "_OFF" "*" "_Y")
      (foreach VAL LAYLST (command "_ON" VAL))
      (command "")
      
      (if (= (length LAYLST) 1)
	(prompt (strcat "\nLayer " (car LAYLST) " has been isolated."))
	(prompt (strcat "\n" (itoa (length LAYLST)) " layers have been isolated. "
			"Layer " LAY " is current."
		)
	)
      )
    )
  )

  (restore_old_error)

  (princ)
)
; -------------------- ISOLATE LAYER FUNCTION --------------------
; Isolates selected object's layer by turning all other layers off
; ----------------------------------------------------------------

(Defun C:qw (/ SS CNT LAY LAYLST VAL)

;  (init_bonus_error 
;    (list
;      (list "cmdecho" 0
;           "expert"  0
;      )
;      T     ;flag. True means use undo for error clean up.  
;    );list  
;  );init_bonus_error

  (if (not (setq SS (ssget "i")))
    (progn
      (prompt "\nSelect object(s) on the layer(s) to be ISOLATED: ")
      (setq SS (ssget))
    )
  )

  (if SS
    (progn

      (setq CNT 0)

      (while (setq LAY (ssname SS CNT))
	(setq LAY (cdr (assoc 8 (entget LAY))))
	(if (not (member LAY LAYLST))
	  (setq LAYLST (cons LAY LAYLST))
	)
	(setq CNT (1+ CNT))
      )

      (if (member (getvar "CLAYER") LAYLST)
	(setq LAY (getvar "CLAYER"))
	(setvar "CLAYER" (setq LAY (last LAYLST)))
      )

      (command "_.-LAYER" "_OFF" "*" "_Y")
      (foreach VAL LAYLST (command "_ON" VAL))
      (command "")
      
      (if (= (length LAYLST) 1)
	(prompt (strcat "\nLayer " (car LAYLST) " has been isolated."))
	(prompt (strcat "\n" (itoa (length LAYLST)) " layers have been isolated. "
			"Layer " LAY " is current."
		)
	)
      )
    )
  )

  (restore_old_error)

  (princ)
)



; -------------------- ISOLATE LAYER FUNCTION --------------------
; Isolates selected object's layer by turning all other layers off
; ----------------------------------------------------------------

(Defun C:OL (/ SS CNT LAY LAYLST VAL)

;  (init_bonus_error 
;    (list
;      (list "cmdecho" 0
;           "expert"  0
;      )
;      T     ;flag. True means use undo for error clean up.  
;    );list  
;  );init_bonus_error

  (if (not (setq SS (ssget "i")))
    (progn
      (prompt "\nSelect object(s) on the layer(s) to be ISOLATED: ")
      (setq SS (ssget))
    )
  )

  (if SS
    (progn

      (setq CNT 0)

      (while (setq LAY (ssname SS CNT))
	(setq LAY (cdr (assoc 8 (entget LAY))))
	(if (not (member LAY LAYLST))
	  (setq LAYLST (cons LAY LAYLST))
	)
	(setq CNT (1+ CNT))
      )

      (if (member (getvar "CLAYER") LAYLST)
	(setq LAY (getvar "CLAYER"))
	(setvar "CLAYER" (setq LAY (last LAYLST)))
      )

      (command "_.-LAYER" "_OFF" "*" "_Y")
      (foreach VAL LAYLST (command "_ON" VAL))
      (command "")
      
      (if (= (length LAYLST) 1)
	(prompt (strcat "\nLayer " (car LAYLST) " has been isolated."))
	(prompt (strcat "\n" (itoa (length LAYLST)) " layers have been isolated. "
			"Layer " LAY " is current."
		)
	)
      )
    )
  )

  (restore_old_error)

  (princ)
)


; -------------------- LAYER FREEZE FUNCTION ---------------------
; Freezes selected object's layer
; ----------------------------------------------------------------

(defun C:LAYFRZ ()
  (layproc "frz")
  (princ)
)

; ---------------------- LAYER OFF FUNCTION ----------------------
; Turns selected object's layer off
; ----------------------------------------------------------------

(defun C:LAYOFF ()
  (layproc "off")
  (princ)
)

; ------------- LAYER PROCESSOR FOR LAYOFF & LAYFRZ --------------
; Main program body for LAYOFF and LAYFRZ. Provides user with
; options for handling nested entities.
; ----------------------------------------------------------------

(defun LAYPROC ( TASK / NOEXIT OPT BLKLST CNT EN PMT ANS LAY NEST BLKLST)


; --------------------- Error initialization ---------------------

  (init_bonus_error 
    (list
      (list "cmdecho" 0
	    "expert"  0
      )

      nil     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error

; -------------------- Variable initialization -------------------

  (setq NOEXIT T)

  (setq OPT (getcfg (strcat "AppData/AC_Bonus/Lay" TASK)))    ; get default option setting
  (if (not (or (null OPT) (= OPT ""))) (setq OPT (atoi OPT)))

  (setq CNT 0)                                                ; cycle counter


  (while NOEXIT

    (initget "Options Undo")
    (if (= TASK "off")
      (setq EN (nentsel "\nOptions/Undo/<Pick an object on the layer to be turned OFF>: "))
      (setq EN (nentsel "\nOptions/Undo/<Pick an object on the layer to be FROZEN>: "))
    )

; ------------------------- Set Options --------------------------

    (While (= EN "Options")
      (initget "No Block Entity")
      (cond
	((= OPT 1)
	  (setq PMT "\nBlock level nesting/Entity level nesting/<No nesting>: ")
	)
	((= OPT 2)
	  (setq PMT "\nBlock level nesting/No nesting/<Entity level nesting>: ")
	)
	(T
	  (setq PMT "\nEntity level nesting/No nesting/<Block level nesting>: ")
	)
      )
      (setq ANS (getkword PMT))

      (cond
	((null ANS)
	  (if (or (null OPT) (= OPT ""))
	    (progn
	      (print ANS)
	      (setq OPT 3)
	      (setcfg (strcat "AppData/AC_Bonus/Lay" TASK) "3")
	    )
	  )
	)
	((= ANS "No")
	  (setq OPT 1)
	  (setcfg (strcat "AppData/AC_Bonus/Lay" TASK) "1")
	)
	((= ANS "Entity")
	  (setq OPT 2)
	  (setcfg (strcat "AppData/AC_Bonus/Lay" TASK) "2")
	)
	(T
	  (setq OPT 3)
	  (setcfg (strcat "AppData/AC_Bonus/Lay" TASK) "3")
	)
      )

      (initget "Options")
      (if (= TASK "off")
	(setq EN (nentsel "\nOptions/Undo/<Pick an object on the layer to be turned OFF>: "))
	(setq EN (nentsel "\nOptions/Undo/<Pick an object on the layer to be FROZEN>: "))
      )
    )

; ------------------------- Find Layer ---------------------------

    (if (and EN (not (= EN "Undo")))
      (progn

	(setq BLKLST (last EN))
	(setq NEST (length BLKLST))

	(cond

      ; If the entity is not nested or if the option for entity
      ; level nesting is selected.
    
	  ((or (= OPT 2) (< (length EN) 3))
	    (setq LAY (entget (car EN)))
	  )
  
      ; If no nesting is desired

	  ((= OPT 1)
	    (setq LAY (entget (car (reverse BLKLST))))
	  )

      ; All other cases (default)

	  (T
	    (setq BLKLST (reverse BLKLST))
	    
	    (while (and                         ; strip out xrefs
		( > (length BLKLST) 0)
		(assoc 1 (tblsearch "BLOCK" (cdr (assoc 2 (entget (car BLKLST))))))
		   );and
	      (setq BLKLST (cdr BLKLST))
	    )
	    (if ( > (length BLKLST) 0)          ; if there is a block present
	      (setq LAY (entget (car BLKLST)))  ; use block layer
	      (setq LAY (entget (car EN)))      ; else use layer of nensel
	    )
	  )
	)

; ------------------------ Process Layer -------------------------

	(setq LAY (cdr (assoc 8 LAY)))
  
	(if (= LAY (getvar "CLAYER"))
	  (if (= TASK "off")
	    (progn
	      (prompt (strcat "\nReally want layer " LAY " (the CURRENT layer) off? <N>: "))
	      (setq ANS (strcase (getstring)))
	      (if (not (or (= ANS "Y") (= ANS "YES")))
		(setq LAY nil)
	      )
	    )
	    (progn
	      (prompt (strcat "\nCannot freeze layer " LAY".  It is the CURRENT layer."))
	      (setq LAY nil)
	    )
	  )
	  (setq ANS nil)
	)
  
	(if LAY
	  (if (= TASK "off")
	    (progn
	      (if ANS
		(command "_.-LAYER" "_OFF" LAY "_Yes" "")
		(command "_.-LAYER" "_OFF" LAY "")
	      )
	      (prompt (strcat "\nLayer " LAY " has been turned off."))
	      (setq CNT (1+ CNT))
	    )
	    (progn
	      (command "_.-LAYER" "_FREEZE" LAY "")
	      (prompt (strcat "\nLayer " LAY " has been frozen."))
	      (setq CNT (1+ CNT))
	    )
	  )
	)
      )

; -------------- Nothing selected or Undo selected ---------------

      (progn
	(if (= EN "Undo")
	  (if (> CNT 0)
	    (progn
	      (command "_.u")
	      (setq CNT (1- CNT))
	    )
	    (prompt "\nEverything has been undone.")
	  )
	  (setq NOEXIT nil)
	)
      )
    )
  )

  (restore_old_error)

)

; --------------------- LAYER LOCK FUNCTION ----------------------
; Locks selected object's layer
; ----------------------------------------------------------------

(Defun C:LAYLCK (/ LAY)

  (init_bonus_error 
    (list
      (list "cmdecho" 0
	    "expert"  0
      )

      T     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error

  (setq LAY (entsel "\nPick an object on the layer to be LOCKED: "))

  (if LAY
    (progn
      (setq LAY (cdr (assoc 8 (entget (car LAY)))))
      (Command "_.-LAYER" "_LOCK" LAY "")
      (prompt (strcat "\nLayer " LAY " has been locked."))
    )
  )

  (restore_old_error)

  (princ)
)

; -------------------- LAYER  FUNCTION ---------------------
; Unlocks selected object's layer
; ----------------------------------------------------------------

(Defun C:LAYULK (/ LAY)

  (init_bonus_error 
    (list
      (list "cmdecho" 0
	    "expert"  0
      )

      T     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error

  (setq LAY (entsel "\nPick an object on the layer to be UNLOCKED: "))

  (if LAY
    (progn
      (setq LAY (cdr (assoc 8 (entget (car LAY)))))
      (Command "_.-LAYER" "_UNLOCK" LAY "")
      (prompt (strcat "\nLayer " LAY " has been unlocked."))
    )
  )

  (restore_old_error)

  (princ)
)

; ---------------------- LAYER ON FUNCTION -----------------------
; Turns all layers on
; ----------------------------------------------------------------

(Defun C:LAYON ()

  (init_bonus_error 
    (list
      (list "cmdecho" 0)
      nil     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error

  (Command "_.-LAYER" "_ON" "*" "")
  (prompt "\nAll layers have been turned on.")

  (restore_old_error)

  (princ)
)


; --------------------- LAYER THAW FUNCTION ----------------------
; Thaws all layers 
; ----------------------------------------------------------------

(Defun C:LAYTHW ()

  (init_bonus_error 
    (list
      (list "cmdecho" 0)
      nil     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error

  (Command "_.-LAYER" "_THAW" "*" "")
  (prompt "\nAll layers have been thawed.")

  (restore_old_error)

  (princ)
)


; --------------------- LAYER MATCH FUNCTION ---------------------
; Changes the layer of selected object(s) to the layer of a
; selected destination object.
; ----------------------------------------------------------------

(Defun C:LAYMCH (/ SS CNT LOOP LAY ANS)

  (init_bonus_error 
    (list
      (list "cmdecho" 0)
      T     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error


  (if (not (setq SS (ssget "i")))
    (progn
      (prompt "\nSelect objects to be changed: ")
      (setq SS (ssget))
    )
  )

  (if SS
    (progn
      (setq CNT (sslength SS))
      (princ (strcat "\n" (itoa CNT) " found."))      ; Report number of items found

      (command "_.move" SS "")                         ; filter out objects on locked layers

      (if (> (getvar "cmdactive") 0)                   ; if there are still objects left
	(progn
	  (command "0,0" "0,0")
	  (setq SS  (ssget "p")
		CNT (- CNT (sslength SS))              ; count them
	  )
	)
	(setq SS nil)                                  ; else abort operation
      ) 

      (if (> CNT 0)                                    ; if items where filtered out
	(if (= CNT 1)
	  (princ (strcat "\n" (itoa CNT) " was on a locked layer."))   ; report it.
	  (princ (strcat "\n" (itoa CNT) " were on a locked layer."))
	)
      )
    )
  )


  (if SS
    (progn
      (initget "Type")
      (setq LAY  (entsel "\nType name/Select entity on destination layer: ")
	    LOOP T
      )
      
      (while LOOP
	(cond
	  ((not LAY)
	    (prompt "\nNothing selected.")
	    (prompt "\nUse current layer? <Y> ")
	    (setq ANS (strcase (getstring)))
	    (if (or (= ANS "") (= ANS "Y") (= ANS "YES"))
	      (setq LAY  (getvar "clayer")
		    LOOP nil
	      )
	    )
	  )
	  ((listp LAY)
	    (setq LOOP nil)
	  )
	  ((= LAY "Type")
	    (setq LAY (getstring "\nEnter layer name: "))
	    (cond
	      ((tblobjname "LAYER" LAY)
		(setq LOOP nil)
	      )
	      ((/= LAY "")
		(prompt "\nLayer does not exist. Would you like to create it? <Y>: ")
		(setq ANS (strcase (getstring)))
		(if (or (= ANS "") (= ANS "Y") (= ANS "YES"))
		  (if
		    (entmake (list
			      '(0 . "LAYER")
			      '(100 . "AcDbSymbolTableRecord")
			      '(100 . "AcDbLayerTableRecord")
			      '(6 . "CONTINUOUS")
			      '(62 . 7)
			      '(70 . 0)
			       (cons 2 LAY)
			     )
		    )
		    (setq LOOP nil)
		    (prompt "\nInvalid Layer name.")
		  )
		)
	      )
	    )
	  )
	)
	(if LOOP
	  (progn
	    (initget "Type")
	    (setq LAY (entsel "\nType name/Select entity on destination layer: "))
	  )
	)
      ); while LOOP
	

      (if (listp LAY)
	(setq LAY (cdr (assoc 8 (entget (car LAY)))))
      )

      (command "_.change" SS "" "_p" "_la" LAY "")

      (if (= (sslength SS) 1)
	(prompt (strcat "\nOne object changed to layer " LAY ))
	(prompt (strcat "\n" (itoa (sslength SS)) " objects changed to layer " LAY ))
      )
      (if (= LAY (getvar "clayer"))
	(prompt " (the current layer).")
	(prompt ".")
      )
    )
  )

  (restore_old_error)

  (princ)
)

; --------------- CHANGE TO CURRENT LAYER FUNCTION ---------------
; Changes the layer of selected object(s) to the current layer
; ----------------------------------------------------------------

(Defun C:LAYCUR (/ SS CNT LAY)

  (init_bonus_error 
    (list
      (list "cmdecho" 0)
      T     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error


  (if (not (setq SS (ssget "i")))
    (progn
      (prompt "\nSelect objects to be CHANGED to the current layer: ")
      (setq SS (ssget))
    )
  )

  (if SS
    (progn
      (setq CNT (sslength SS))
      (princ (strcat "\n" (itoa CNT) " found."))      ; Report number of items found

      (command "_.move" SS "")                         ; filter out objects on locked layers

      (if (> (getvar "cmdactive") 0)                   ; if there are still objects left
	(progn
	  (command "0,0" "0,0")
	  (setq SS  (ssget "p")
		CNT (- CNT (sslength SS))              ; count them
	  )
	)
	(setq SS nil)                                  ; else abort operation
      ) 

      (if (> CNT 0)                                    ; if items where filtered out
	(if (= CNT 1)
	  (princ (strcat "\n" (itoa CNT) " was on a locked layer."))   ; report it.
	  (princ (strcat "\n" (itoa CNT) " were on a locked layer."))
	)
      )
    )
  )

  (if SS
    (progn
      (setq LAY (getvar "CLAYER"))
      (command "_.change" SS "" "_p" "_la" LAY "")
      (if (= (sslength SS) 1)
	(prompt (strcat "\nOne object changed to layer " LAY " (the current layer)."))
	(prompt (strcat "\n" (itoa (sslength SS)) " objects changed to layer " LAY " (the current layer)."))
      )
    )
  )

  (restore_old_error)

  (princ)
)

(prompt "\nAutoCAD Bonus Layer Tools Loaded.")
(princ)









;A0 ***** change to layer 0 *****
(defun c:A1()
	(command "layer" "t" "0" "s" "0" "U" "0" ""))
(defun c:41()
	(command "layer" "t" "41" "s" "41" "u" "41" ""))
;FA ***** all of layer turn on ,thaw and unlock *****
(defun c:fa()
	(command "layer" "t" "*" "on" "*" "u" "*" "")
	(command "layer" "off" "0paperf" ""))
;FB ***** all of layer turn on ,thaw and unlock *****
(defun c:fB()
	(command "layer" "t" "*" "on" "*" "u" "*" ""))
;A3,A4******** INSERT A3,A4 TUKUANG ***********
(DEFUN C:A4()
	 (setvar "cmdecho" 0)
	 (setq e1 (getstring "\n Input the scale:"))
	 (command "dimscale" e1)
	 (COMMAND "INSERT" 
		  "K:\\U10984\\?}?J\\???J??\\009.DWG" pause e1 e1 "0"))
(DEFUN C:A3()
	 (setvar "cmdecho" 0)
	 (setq e1 (getstring "\n Input the scale:"))
	 (setq E2 (GETPOINT "\n Input insert point:"))
	 (COMMAND "INSERT" 
		   "K:\\U10984\\?}?J\\???J??\\008.DWG" E2 e1 e1 "0"))
(DEFUN C:BOM()
	 (setvar "cmdecho" 0)
	 (setq pt (getpoint "\n input insert point:"))
	 (command "insert" "k:\\u10984\\?}?J\\???J??\\010.dwg" 1 1 1 0))
;-------------DIM MODIFIED--------------
(defun c:y()
	    (setvar "cmdecho" 0)
	    (prompt "\nInput scale of the DIM <")
	    (setq m (getvar "dimscale"))
	    (prin1 m)
	    (setq m (getreal ">:"))
	    (command "dimtxt" 2)
	    (command "layer" "t" "41" "s" "41" "u" "41" "")
	    (command "dimtxsty" "simplex")
	    (command "dimscale" m)
	    (command "dimtxsty" "simplex")
	    (command "dimtxt" 2) (command "dimdli" 2.5)
	    (command "dimgap" 0.5)
	    (command "dimexo" 0.625) (command "dimasz" 2.5)
	    (command "dimtofl" "on") (command "dimtih" "off")
	    (command "dimexe" 1) (command "dimzin" 8)
	    (command "dimtzin" 8)(setvar "cmdecho" 1))



(defun c:e1()
	   (prompt "\n(Select dim. to be modified)") (ssget)
	   (command "dimoverride" "dimZIN" "0" "dimdec" "1" "" "p" ""))
	  ;(command "dimoverride" "dimdec" "1" "" "p" ""))
(defun c:EE()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimZIN" "0" "dimdec" "0" "" "p" ""))
(defun c:EEE()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimZIN" "8" "dimdec" "3" "" "p" ""))
(defun c:e2()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimZIN" "0" "dimdec" "2" "" "p" ""))
(defun c:e3()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimZIN" "0" "dimdec" "3" "" "p" ""))
(defun c:dec()
	  (prompt "\n(Sets DIM's decimal point)")
	  (setq z (getstring "\nInput a Number(0 to 8 only):"))
	  (command "dimdec" z))
(defun c:tad()
	  (prompt "\n(Controls text in relation to the dimension line)")
	  (setq z1 (getstring "\nInput a Number(0 or 1 only)"))
	  (command "dimtad" z1))
(defun c:d2()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimtad" "0" "" "p" ""))
(defun c:d1()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimtad" "1" "" "p" ""))
(defun c:t2()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimtoh" "off" "" "p" ""))
(defun c:t1()
	  (prompt "\n(Select dim. to be modified)") (ssget)
	  (command "dimoverride" "dimtoh" "on" "" "p" ""))
(defun c:DD2()
	  (command "dimdli" 2.5))
(defun c:DD4()
	  (command "dimdli" 4.5))
;Ds ***** TO CHANGE DIM LINEAR FACTOR
(defun c:Ds() 
  (setvar "cmdecho" 0)
  (if (= LF nil) (setq LF 1.0))
  (prompt "\nInput DIM scale coefficient to be modified<")
  (prin1 LF)
  (setq LF (getreal ">:"))
  (if (= LF nil) (setq LF 1.0))
  (command "dimoverride" "DIMLFAC" (/ 1.0 LF) "")
  (setvar "cmdecho" 1))
(defun c:dsx()
  (setvar "cmdecho" 0)
  (if (= ds nil) (setq ds 1.0))
  (prompt "\nInput DIM scale coefficient<")
  (prin1 ds)
  (setq ds (getreal ">:"))
  (command "dimlfac" (/ 1.0 ds))
  (setvar "cmdecho" 1))
(defun c:ds1()
	  (command "dimlfac" 1))
;|(defun c:V()
	(command "color" "bylayer" "")
	(command "celtype" "bylayer" ""))
|;

;B1 *** PARTS NUMBER
(defun C:B1()
  (graphscr)
  (setq oce (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (setq mydimscale (getvar "dimscale"))
  (if (= myDimscale nil) (setq mydimscale 1))
  (setq
    p1 (getpoint "\First point:")
    p2 (getpoint p1 "\Bubber center point:")
    a1 (angle p2 p1)
    p3 (polar p2 a1 (* 4 mydimscale) )
    t1 (getstring "Number:")
  )
  (command "LINE" p1 p3 "")
  (command "CIRCLE" p2 (* 4 mydimscale) )
  (Command "TEXTSTYLE" "simplex")
  (command "TEXT" "M" p2 (* 2.0 mydimscale) 0 t1)
  (setvar "cmdecho" oce)
  (princ))
;B2 *** PARTS NUMBER
(defun C:B2()
  (graphscr)
  (setq oce (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (setq mydimscale (getvar "dimscale"))
  (if (= myDimscale nil) (setq mydimscale 1))
  (setq
    d1 (* 8.5 mydimscale)
    p1 (getpoint "\nFirst point:")
    p2 (getpoint "\nFirst bubber center point:")
    a1 (angle p2 p1))
  (if (> a1 (* 1.5 pi)) (setq d1 (* -1 d1)))
  (setq
    p4 (polar p2 0 d1)
    p3 (polar p2 a1 (* 4 mydimscale))
    t1 (getstring "\nNumber one:")
    t2 (getstring "\nNnmber two:"))
  (command "LINE" p1 p3 "")
  (command "CIRCLE" p2 (* 4 mydimscale))
  (command "circle" p4 (* 4 mydimscale))
  (Command "TEXTSTYLE" "simplex")
  (command "TEXT" "M" p2 (* 2.0 mydimscale) 0 t1)
  (command "TEXT" "M" p4 (* 2.0 mydimscale) 0 t2)
  (setvar "cmdecho" oce)
  (princ))
;cham 0
(defun c:C1()
	    (command "chamfer" "d" 0 0)
	    (command "chamfer"))
;C1 ***** chamfer cc=1
      (defun c:Ch1()
	    (command "chamfer" "d" 1 1)
	    (command "chamfer"))
;---------------------------------------------
;C2 ***** chamfer cc=2
      (defun c:Ch2()
	    (command "chamfer" "d" 2 2)
	    (command "chamfer"))
;---------------------------------------------

;C3 ***** chamfer cc=3
      (defun c:Ch3()
	    (command "chamfer" "d" 3 3)
	    (command "chamfer"))
;---------------------------------------------
;C4 ***** chamfer cc=4
      (defun c:Ch4()
	    (command "chamfer" "d" 4 4)
	    (command "chamfer"))
;---------------------------------------------

;C5 ***** chamfer cc=5
      (defun c:Ch5()
	    (command "chamfer" "d" 5 5)
	    (command "chamfer"))
;---------------------------------------------
;C6 ***** chamfer cc=6
      (defun c:Ch6()
	    (command "chamfer" "d" 6 6)
	    (command "chamfer"))
;---------------------------------------------
;C8 ***** chamfer cc=8
      (defun c:Ch8()
	    (command "chamfer" "d" 8 8)
	    (command "chamfer"))
;---------------------------------------------

;C10 ***** chamfer cc=10
      (defun c:Ch10()
	    (command "chamfer" "d" 10 10)
	    (command "chamfer"))
;---------------------------------------------

;C20 ***** chamfer cc=20
      (defun c:Ch20()
	    (command "chamfer" "d" 20 20)
	    (command "chamfer"))
;---------------------------------------------
;C0.1 ***** chamfer cc=0.1
      (defun c:Ch01()
	    (command "chamfer" "d" 0.1 0.1)
	    (command "chamfer"))

;---------------------------------------------
;C0.2 ***** chamfer cc=0.2
      (defun c:Ch02()
	    (command "chamfer" "d" 0.2 0.2)
	    (command "chamfer"))

;---------------------------------------------
;C0.3 ***** chamfer cc=0.3
      (defun c:Ch03()
	    (command "chamfer" "d" 0.3 0.3)
	    (command "chamfer"))

;---------------------------------------------
;C0.5 ***** chamfer cc=0.5
      (defun c:Ch05()
	    (command "chamfer" "d" 0.5 0.5)
	    (command "chamfer"))









;F1 ***** FILLET R==1
      (defun c:F1()
	    (command "FILLET" "R" 1)
	    (command "FILLET"))
;---------------------------------------------
;F2 ***** FILLET R==2
      (defun c:F2()
	    (command "FILLET" "R" 2)
	    (command "FILLET"))
;---------------------------------------------

;F3 ***** FILLET R==3
      (defun c:F3()
	    (command "FILLET" "R" 3)
	    (command "FILLET"))
;---------------------------------------------
;F4 ***** FILLET R==4
      (defun c:F4()
	    (command "FILLET" "R" 4)
	    (command "FILLET"))
;---------------------------------------------

;F5 ***** FILLET R==5
      (defun c:F5()
	    (command "FILLET" "R" 5)
	    (command "FILLET"))
;---------------------------------------------
;F6 ***** FILLET R==6
      (defun c:F6()
	    (command "FILLET" "R" 6)
	    (command "FILLET"))
;---------------------------------------------
;F8 ***** FILLET R==8
      (defun c:F8()
	    (command "FILLET" "R" 8)
	    (command "FILLET"))
;---------------------------------------------

;F10 ***** FILLET R==10
      (defun c:F10()
	    (command "FILLET" "R" 10)
	    (command "FILLET"))
;---------------------------------------------

;F20 ***** FILLET R==20
      (defun c:F20()
	    (command "FILLET" "R" 20)
	    (command "FILLET"))
;---------------------------------------------
;F0.1 ***** FILLET R==0.1
      (defun c:F01()
	    (command "FILLET" "R" 0.1)
	    (command "FILLET"))

;---------------------------------------------
;F0.2 ***** FILLET R==0.2
      (defun c:F02()
	    (command "FILLET" "R" 0.2)
	    (command "FILLET"))

;---------------------------------------------
;F0.3 ***** FILLET R==0.3
      (defun c:F03()
	    (command "FILLET" "R" 0.3)
	    (command "FILLET"))

;---------------------------------------------
;F0.5 ***** FILLET R==0.5
      (defun c:F05()
	    (command "FILLET" "R" 0.5)
	    (command "FILLET"))





















;fe ***** TO ADD %%c BEFORE DIM
      (defun c:fe() (command "dimoverride" "DIMPOST" "\\U+2205<>" ""))
;ff -------- input a DIM--------------
(defun c:ff()
      (setvar "cmdecho" 0)
      (setq myosmode (getvar "osmode"))
      (setq mydimtad (getvar "dimtad"))
      (setq mydimscale (getvar "dimscale"))
      (setvar "osmode" 0)
      (setvar "osmode" 1) (setvar "dimtad" 0)
      (setq pt0 (getpoint "Input origin:"))
      (command "ucs" "o" pt0)
      (command "dimordinate" "0,0" pause )(setvar "osmode" 0)(setvar "osmode" 1)
      (command "dimcontinue" pause)
      (setvar "osmode" myosmode) )

;************LAYISO OL*****************
(Defun C:OL (/ SS CNT LAY LAYLST VAL)
  (init_bonus_error 
    (list
      (list "cmdecho" 0
	    "expert"  0
      )
      T     ;flag. True means use undo for error clean up.  
    );list  
  );init_bonus_error
  (if (not (setq SS (ssget "i")))
    (progn
      (prompt "\nSelect object(s) on the layer(s) to be ISOLATED: ")
      (setq SS (ssget))
    )
  )
  (if SS
    (progn
      (setq CNT 0)
      (while (setq LAY (ssname SS CNT))
	(setq LAY (cdr (assoc 8 (entget LAY))))
	(if (not (member LAY LAYLST))
	  (setq LAYLST (cons LAY LAYLST))
	)
	(setq CNT (1+ CNT))
      )
      (if (member (getvar "CLAYER") LAYLST)
	(setq LAY (getvar "CLAYER"))
	(setvar "CLAYER" (setq LAY (last LAYLST)))
      )
      (command "_.-LAYER" "_OFF" "*" "_Y")
      (foreach VAL LAYLST (command "_ON" VAL))
      (command "")
      (if (= (length LAYLST) 1)
	(prompt (strcat "\nLayer " (car LAYLST) " has been isolated."))
	(prompt (strcat "\n" (itoa (length LAYLST)) " layers have been isolated. "
			"Layer " LAY " is current."
		)
	)
      )
    )
  )
  (restore_old_error)
  (princ)
)
(defun c:MM3()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF SCREW:"))
	(setq x (strcat e1 "-\M3*0.5 Thru"))
	   (IF (= e1 "1")             
	      (setq x (strcat "M3*0.5 Thru")) 
	    )
	(COMMAND "TEXTSTYLE" "SIMPLEX")
	(command "leader" "nearest" pause pause "" x ""))
(defun c:MM4()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\nInput the NUMBER of screw:"))
	(setq x (strcat e1 "-\M4*0.7 Thru"))
	   (IF (= e1 "1")             
	      (setq x (strcat "M4*0.7 Thru")) ZZ
	    )
	(COMMAND "TEXTSTYLE" "SIMPLEX")
	(command "leader" "nearest" pause pause "" x ""))
(defun c:MM5()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\nInput the No. of screw:"))
	(setq x (strcat e1 "-\M5*0.8 Thru"))
	   (IF (= e1 "1")             
	      (setq x (strcat "M5*0.8 Thru")) 
	    )
	(COMMAND "TEXTSTYLE" "SIMPLEX")
	(command "leader" "nearest" pause pause "" x ""))
(defun c:MM6()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\nInput the No. of screw:"))
	(setq x (strcat e1 "-\M6*1.0 Thru"))
	   (IF (= e1 "1")             
	      (setq x (strcat "M6*1.0 Thru")) 
	    )
	(COMMAND "TEXTSTYLE" "SIMPLEX")
	(command "leader" "nearest" pause pause "" x ""))
(defun c:MM8()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\nInput the No. of screw:"))
	(setq x (strcat e1 "-\M8*1.25 Thru"))
	   (IF (= e1 "1")             
	      (setq x (strcat "M8*1.25 Thru")) 
	    )
	(COMMAND "TEXTSTYLE" "SIMPLEX")
	(command "leader" "nearest" pause pause "" x ""))
(defun c:MM10()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\nInput the No. of screw:"))
	(setq x (strcat e1 "-\M10*1.5 Thru"))
	   (IF (= e1 "1")             
	      (setq x (strcat "M10*1.5 Thru")) 
	    )
	(COMMAND "TEXTSTYLE" "SIMPLEX")
	(command "leader" "nearest" pause pause "" x ""))
(defun c:MM12()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\nInput the No. of screw:"))
	(setq x (strcat e1 "-\M12*1.75 Thru"))
	   (IF (= e1 "1")             
	      (setq x (strcat "M12*1.75 Thru")) 
	    )
	(COMMAND "TEXTSTYLE" "SIMPLEX")
	(command "leader" "nearest" pause pause "" x ""))
;-----------------FILLET---------------
;r1 ***** fillet r=1
      (defun c:r1()
	    (command "fillet" "r" 1)
	    (command "fillet"))
;---------------------------------------------
      (defun c:r2()
	    (command "fillet" "r" 2)
	    (command "fillet"))
;---------------------------------------------
      (defun c:r5()
	    (command "fillet" "r" 5)
	    (command "fillet"))


;|---------------------------------------------
(defun c:r0()
	    (command "fillet" "r" 10)
	    (command "fillet"))
(DEFUN C:1()
	 (setq dsc (getvar "dimscale")) 
	 (COMMAND "INSERT"
		  "K:\\U10984\\?}?J\\???J??\\003.DWG" PAUSE dsc dsc 0))
(DEFUN C:2()
	 (setq dsc (getvar "dimscale")) 
	 (COMMAND "INSERT"
		  "K:\\U10984\\?}?J\\???J??\\006.DWG" PAUSE dsc dsc 0))
(DEFUN C:3()
	 (setq dsc (getvar "dimscale")) 
	 (COMMAND "INSERT"
		  "K:\\U10984\\?}?J\\???J??\\002.DWG" PAUSE dsc dsc 0))
(DEFUN C:4()
	 (setq dsc (getvar "dimscale"))
	 (COMMAND "INSERT"
		  "K:\\U10984\\?}?J\\???J??\\001.DWG" PAUSE dsc dsc 0))
(DEFUN C:5()
	 (setq dsc (getvar "dimscale"))
	 (COMMAND "INSERT" 
		  "K:\\U10984\\?}?J\\???J??\\004.DWG" PAUSE dsc dsc 0))
(DEFUN C:6()
	 (setq dsc (getvar "dimscale")) 
	 (COMMAND "INSERT"
		  "K:\\U10984\\?}?J\\???J??\\005.DWG" PAUSE dsc dsc 0))
(DEFUN C:7()
	 (setq dsc (getvar "dimscale")) 
	 (COMMAND "INSERT"
		  "K:\\U10984\\?}?J\\???J??\\007.DWG" PAUSE dsc dsc 0))



|;

			   ~~~~~~~~~~~~~~~~~~~~~~
			   ~     WILLION.LISP   ~    
			   ~~~~~~~~~~~~~~~~~~~~~~

						     04/25'02
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

;CS ***** CHANGE TEXT SIZE *****
(defun c:CS()
	(command "change" pause "" "" "" "" ".8" "" "" )
)
;A4 ***** INSERT A4 DWG *****
(defun c:A4()
	(command "INSERT"  "K:\\U18544\\A4.DWG"  )
)
;CT ***** CHANGE TEXT STYLE *****
(defun c:CT()
	(command "change" pause "" "" "" "SIMPLEX" "2.5" "" "" )
)
;Cq ***** CHANGE PART NO. *****
(defun c:Cq()
	(command "change" pause "" "" "" "" "" "" "PZ47*8-****-**" )
)
;CE ***** CHANGE TEXT CONTANT *****
(defun c:CE()
	(command "change" pause "" "" "" "" "" "" "BC98281" )
)
;CN ***** CHANGE TEXT CONTANT *****
(defun c:CN()
	(command "change" pause "" "" "" "" "" "" "CONTACT INSERTING FIXTURE" )
	)
;CN ***** CHANGE TEXT ECN NO. *****
(defun c:C1()
	(command "change" pause "" "" "" "" "" "" "BC0224888" )
	)
;D?  ***** note for c_bore of ******

(defun c:C3()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22053.4 Thru\\P\n\n\\U+22056.5 Dep3.4"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C4()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22054.5 Thru\\P\n\n\\U+22058.0 Dep4.5"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C5()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22055.5 Thru\\P\n\n\\U+22059.5 Dep5.5"))
	(command "leader" "nearest" pause pause "" x "")
)       
(defun c:C6()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22056.5 Thru\\P\n\n\\U+220511.0 Dep6.5"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:C8()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22059.0 Thru\\P\n\n\\U+220514.0 Dep9.0"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H3()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22053.4 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H4()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22054.5 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H5()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22055.5 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)       
(defun c:H6()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22056.5 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)
(defun c:H8()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CBORE :"))
	(setq x (strcat e1 "-\\U+22059.0 Thru"))
	(command "leader" "nearest" pause pause "" x "")
)

;---------------------------------------------
;LE ***** leader note   
	(defun c:LE()
	    (command "leader" "nearest" pause pause pause "" )
	)
;------ DIMENSION LISP -----------------------
;TS ****** CHANGE TEXT SCALE ******
(defun c:TS()
	(graphscr)
	(setvar "cmdecho" 0)
	(setq stmp myTEXTScale)
	(prompt "\ninput TEXTScale :")
	(prin1 myTEXTScale)
	(setq myTEXTScale (getreal "> :"))
	(if (= myTEXTscale nil) (setq myTEXTScale stmp))
	(prompt "select TEXT to be changed:")
	(setq e1 (ssget '
	  ((-4 . "<OR") (0 . "TEXT") (0 . "MTEXT") (-4 . "OR>"))))
	(setq i 0)
	(if e1 (progn
	  (repeat (sslength e1)
	       (setq e4 (entget (ssname e1 i)))
	       (setq t_high (cdr (assoc 40 e4)))
	       (setq e2 (cons 40 (* 2.0 myTEXTScale)))
	       (setq e5 (assoc 40 e4))
	       (setq e4 (subst e2 e5 e4))
	       (entmod e4)
	       (setq i (1+ i))
	  )
	  (princ "\nAll selected TEXT change to TEXTHeight :")
	  (princ (cdr e2))
	))
	(setvar "TEXTSIZE" (* 2.0 myTEXTScale))
	(princ)
)
; --------------------------------------
;CDS1 ***** change DIMstyle scale 
(defun c:cds1(/ new_ds new_dtext i dt_d dt ds dt_d e1 )
	(graphscr)
	(setvar "cmdecho" 0)
	(setq myDIMscale (getreal "\ninput DIM SCALE :"))
	(setq new_ds (cons 40 myDIMscale))
	(setq new_dtext (cons 140 2.5))
	(setq i 0)
	(setq dt_d (tblnext "dimstyle" 1))
	(while dt_d
	  (setq dt (entget (tblobjname "dimstyle" (cdr (assoc 2 dt_d)))))
	  (setq ds (assoc 40 dt))
	  (setq dt (subst new_ds ds dt))
	  (setq ds (assoc 140 dt))
	  (setq dt (subst new_dtext ds dt))
	  (entmod dt)
	  (setq dt_d (tblnext "dimstyle"))
	)
	(setq e1 (ssget "X" '((0 . "DIMENSION"))))
	(setq i 0)
	(if e1 (progn
	  (repeat (sslength e1)
	    (setq e4 (entget (ssname e1 i)))
	    (entmod e4)
	    (setq i (1+ i))
	  ) 
	))
	(command "dimstyle" "r" (getvar "DIMSTYLE") )
	(setvar "LTSCALE" (* 3 myDIMscale))
	(setvar "TEXTSIZE" (* 2.5 myDIMscale))
)
;---------------------------------------------
;DI ***** change selected DIM to a identified DIMstyle 
(defun c:DI()
	(graphscr)
	(setvar "cmdecho" 0)
	(setq stmp myDIMstyle)
	(prompt "\ninput DIMSTYLE NAME :")
	(prin1 myDIMstyle)
	(setq myDIMstyle (getstring "> :"))
	(if (= myDIMstyle "") (setq myDIMstyle stmp))
	(prompt "DIM to be changed:")
	(setq e1 (ssget '((0 . "DIMENSION"))))
	(setq e2 (cons 3 myDIMstyle))
	(setq i 0)
	(if e1
	  (progn
	    (repeat (sslength e1)
		 (setq e4 (entget (ssname e1 i)))
		 (setq e5 (assoc 3 e4))
		 (setq e4 (subst e2 e5 e4))
		 (entmod e4)
		 (setq i (1+ i))
	    )
	    (princ "\nAll selected DIM change to DIMstyle :")
	    (princ (cdr e2))
	  )
	)
	(princ)
)
;---------------------------------------------
;DO1 ***** set 41. origin and start to dimension
(defun c:DO1()
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oosmode (getvar "osmode"))
	(command "layer" "t" "41" "on" "41" "unlock" "41" 
			 "s" "41" "")
	(setvar "dimaso" 1)
	(setvar "osmode" 0)
	(command "dimstyle" "r" "1")
	(prompt "Pick the Original Point")
	(command "ucs" "o" pause)
	(princ)
	(command "dimordinate" "0,0" pause)
	(setvar "osmode" 1)
	(command "dimcontinue")
)
;DAC ***** TO ADD %%c BEFORE DIM
      (defun c:DAC() (command "dimoverride" "DIMPOST" "\\U+2205<>" "") )

;DF ***** TO CHANGE DIM LINEAR FACTOR
(defun c:DF() 
  (setvar "cmdecho" 0)
  (setq stmp LF)
  (prompt "\ninput DIM LINEAR FACTOR :")
  (prin1 LF)
  (setq LF (getreal "> :"))
  (if (= LF nil) (setq LF stmp))
  (command "dimoverride" "DIMLFAC" (/ 1.0 LF) "") 
)
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
~12 ~~~~CHANGE PROPERTIES TO BE LAYER=1 & COLOR=BYLAYER & LINETYPE=BYLAYER
(DEFUN C:12()
  (SETVAR "CMDECHO" 1)
  (PROMPT "\n CHANGE PROPERTIES TO BE LAYER=1 & COLOR=BYLAYER & LINETYPE=BYLAYER:")
  (SSGET)
  (COMMAND "CHPROP" "P" "" "LA" 1 "LT" "BYLAYER" "CO" "BYLAYER" "")
  (SETVAR "CMDECHO" 0)
)
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
~11 ~~~~CHANGE PROPERTIES TO BE LAYER=11 & COLOR=BYLAYER & LINETYPE=BYLAYER
(DEFUN C:11()
  (SETVAR "CMDECHO" 1)
  (PROMPT "\n CHANGE PROPERTIES TO BE LAYER=11 & COLOR=BYLAYER & LINETYPE=BYLAYER:")
  (SSGET)
  (COMMAND "CHPROP" "P" "" "LA" 11 "LT" "BYLAYER" "CO" "BYLAYER" "")
  (SETVAR "CMDECHO" 0)
)
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
~41 ~~~~CHANGE PROPERTIES TO BE LAYER=11 & COLOR=BYLAYER & LINETYPE=BYLAYER
(DEFUN C:41()
  (SETVAR "CMDECHO" 1)
  (PROMPT "\n CHANGE PROPERTIES TO BE LAYER=41 & COLOR=BYLAYER & LINETYPE=BYLAYER:")
  (SSGET)
  (COMMAND "CHPROP" "P" "" "LA" 41 "LT" "BYLAYER" "CO" "BYLAYER" "")
  (SETVAR "CMDECHO" 0)
)
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
~51 ~~~~CHANGE PROPERTIES TO BE LAYER=11 & COLOR=BYLAYER & LINETYPE=BYLAYER
(DEFUN C:51()
  (SETVAR "CMDECHO" 1)
  (PROMPT "\n CHANGE PROPERTIES TO BE LAYER=51 & COLOR=BYLAYER & LINETYPE=BYLAYER:")
  (SSGET)
  (COMMAND "CHPROP" "P" "" "LA" 51 "LT" "BYLAYER" "CO" "BYLAYER" "")
  (SETVAR "CMDECHO" 0)
)
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;BB1 *** PARTS NUMBER
(defun C:BB1()
  (graphscr)
  (setq oce (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (if (= myDimscale nil) (setq mydimscale 1))
  (setq
    p1 (getpoint "\First point:")
    p2 (getpoint p1 "\Bubber center point:")
    a1 (angle p2 p1)
    p3 (polar p2 a1 (* 5 mydimscale) )
    t1 (getstring "Number:")
  )
  (command "LINE" p1 p3 "")
  (command "CIRCLE" p2 (* 5 mydimscale) )
  (command "TEXT" "M" p2 (* 2.5 mydimscale) 0 t1)
  (command "DONUT" 0 1 P1 "")

  (setvar "cmdecho" oce)
  (princ)
)

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;AM ***** change selected layer to match a certain entity's layer 
(defun c:AM()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities to be changed:")
	(setq
		e1 (ssget)
		e2 (entsel "\nSelect Target layer Entity")
	)
	(if (and e1 e2)
		(progn
			(setq e2 (assoc 8 (entget (car e2))))
			(setq i 0)
			(repeat (sslength e1)
				(setq e4 (entget (ssname e1 i)))
				(setq e5 (assoc 8 e4))
				(setq e4 (subst e2 e5 e4))
				(entmod e4)
				(setq i (1+ i))
			)
			(princ "\nAll selected entities change to layer ")
			(princ (cdr e2))
		)
	)
	(princ)
)

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;AE ***** change selected layer to match a certain entity's layer 
(defun c:AE()
	(graphscr)
	(setvar "cmdecho" 0)
	(prompt "\nEntities to be changed:")
	(setq
		e1 (ssget)
		e2 (entsel "\nSelect Target layer Entity")
	)
	(if (and e1 e2)
		(progn
			(setq e2 (assoc 8 (entget (car e2))))
			(setq i 0)
			(repeat (sslength e1)
				(setq e4 (entget (ssname e1 i)))
				(setq e5 (assoc 8 e4))
				(setq e4 (subst e2 e5 e4))
				(entmod e4)
				(setq i (1+ i))
			)
			(princ "\nAll selected entities change to layer ")
			(princ (cdr e2))
		)
	)
	(princ)
)
;---------------------------------------------

;CA1 ***** draw a modified sine cam profile for plate cam
      (defun c:CA1()
	(setq pt0 (getpoint "Input center :"))
	(setq center pt0)
	(setq r (getreal "\nBase circle radius ="))
	(setq h (getreal "\nRise ="))
	(setq b0 (getreal "\nAngle of rise ="))
	(setq b1 (getreal "\nAngle of dwell="))
	(setq b2 (getreal "\nAngle of descent ="))
	(setq hpi (/ pi 2.0000))
	(setq b (* (/ b0 180.0000) pi))
	(setq i 1)
	(setq pt1 (polar pt0 hpi r))
	(setq start_pt pt1)
	(command "line" pt0 pt1 "")
	(repeat 15
	    (setq tb (/ i 120.0000))
	      (setq x1 (* 0.44 tb))
	      (setq x2 (* (* 4 pi) tb))
	      (setq x3 (* (sin x2) 0.035))
	      (setq k (- x1 x3))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) hpi) (+ r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
	(repeat 90
	      (setq tb (/ i 120.000))
	      (setq y1 (* 0.44 tb))
	      (setq y1 (+ y1 0.280))
	      (setq y2 (/ 4.000 3.000))
	      (setq y2 (- (* y2 pi tb) (/ pi 6.000)))
	      (setq y2 (* 0.315 (cos y2)))
	      (setq k (- y1 y2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) hpi) (+ r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	      (princ k)
	 )
	 (repeat 15
	      (setq tb (/ i 120.000)) 
	      (setq z1 (* 0.44 tb))
	      (setq z1 (+ z1 0.5601))
	      (setq z2 (- (* 2.000 tb) 1))
	      (setq z2 (* z2 pi 2.000))
	      (setq z2 (* 0.035 (sin z2)))
	      (setq k (- z1 z2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) hpi) (+ r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
	      (setq endr ( + r h))
	      (setq endang (+ b hpi))
;--------------          
	 (command "line" center pt2 "") 
	 (setq dwell1 b1)
	 (setq dwell1 (/ dwell1 180))
	 (setq dwell1 (* dwell1 pi))
	 (setq ang1 (+ endang dwell1))
	 (setq pt1 (polar pt0 ang1 endr)) 
	 (command "line" pt0 pt1 "")
	 (command "arc" "c" center pt2 pt1 "")

;-----------------
	(setq r (+ r h))
	(setq b0 b2)
	(setq hpi (/ pi 2.0000))
	(setq b (* (/ b0 180.0000) pi))
	(setq i 1)
	(repeat 15
	    (setq tb (/ i 120.0000))
	      (setq x1 (* 0.44 tb))
	      (setq x2 (* (* 4 pi) tb))
	      (setq x3 (* (sin x2) 0.035))
	      (setq k (- x1 x3))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) ang1) (- r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
;--------------
	(repeat 90
	      (setq tb (/ i 120.000))
	      (setq y1 (* 0.44 tb))
	      (setq y1 (+ y1 0.280))
	      (setq y2 (/ 4.000 3.000))
	      (setq y2 (- (* y2 pi tb) (/ pi 6.000)))
	      (setq y2 (* 0.315 (cos y2)))
	      (setq k (- y1 y2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) ang1) (- r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
;------------------
	 (repeat 15
	      (setq tb (/ i 120.000)) 
	      (setq z1 (* 0.44 tb))
	      (setq z1 (+ z1 0.5601))
	      (setq z2 (- (* 2.000 tb) 1))
	      (setq z2 (* z2 pi 2.000))
	      (setq z2 (* 0.035 (sin z2)))
	      (setq k (- z1 z2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) ang1) (- r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
      (setq end_pt pt2)
      (command "line" center end_pt "")
      (command "arc" "c" center end_pt start_pt "")  
      (command "color" "red" "")
      (command "linetype" "s" "phantom" "")
      (command "arc" "c" center start_pt end_pt "")
      (command "color" "bylayer" "")
      (command "linetype" "s" "bylayer" "")
  )
;**********************************************************************
;CA2 ***** draw a modified sine cam profile for plate cam
      (defun c:CA2()
	(setq pt0 (getpoint "Input center :"))
	(setq center pt0)
	(setq r (getreal "\nBase circle radius ="))

(setq r (getreal "\nBase circle radius ="))
	(setq h (getreal "\nRise ="))
	(setq b0 (getreal "\nAngle of rise ="))
	(setq b1 (getreal "\nAngle of dwell="))
	(setq b2 (getreal "\nAngle of descent ="))

	(setq h 24.630)
	(setq b0 80.0)
	(setq hpi (/ pi 2.0000))
	(setq b (* (/ b0 180.0000) pi))
	(setq i 1)
	(setq pt1 (polar pt0 hpi r))
	(setq start_pt pt1)
	(command "line" pt0 pt1 "")
	(repeat 15
	    (setq tb (/ i 120.0000))
	      (setq x1 (* 0.44 tb))
	      (setq x2 (* (* 4 pi) tb))
	      (setq x3 (* (sin x2) 0.035))
	      (setq k (- x1 x3))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) hpi) (+ r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
	(repeat 90
	      (setq tb (/ i 120.000))
	      (setq y1 (* 0.44 tb))
	      (setq y1 (+ y1 0.280))
	      (setq y2 (/ 4.000 3.000))
	      (setq y2 (- (* y2 pi tb) (/ pi 6.000)))
	      (setq y2 (* 0.315 (cos y2)))
	      (setq k (- y1 y2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) hpi) (+ r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	      (princ k)
	 )
	 (repeat 15
	      (setq tb (/ i 120.000)) 
	      (setq z1 (* 0.44 tb))
	      (setq z1 (+ z1 0.5601))
	      (setq z2 (- (* 2.000 tb) 1))
	      (setq z2 (* z2 pi 2.000))
	      (setq z2 (* 0.035 (sin z2)))
	      (setq k (- z1 z2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) hpi) (+ r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
	      (setq endr ( + r dl))
	      (setq endang (+ (* tb b) hpi))
;--------------          
	 (command "line" center pt2 "") 
	 (setq dwell1 10.000)
	 (setq dwell1 (/ dwell1 180))
	 (setq dwell1 (* dwell1 pi))
	 (setq ang1 (+ endang dwell1))
	 (setq pt1 (polar pt0 ang1 endr)) 
	 (command "line" pt0 pt1 "")
	 (command "arc" "c" center pt2 pt1 "")

;-----------------
;       (setq r (+ r 25.00 5.00))
	(setq h 24.63)
	(setq b0 60.0)
	(setq hpi (/ pi 2.0000))
	(setq b (* (/ b0 180.0000) pi))
	(setq i 1)
	(repeat 15
	    (setq tb (/ i 120.0000))
	      (setq x1 (* 0.44 tb))
	      (setq x2 (* (* 4 pi) tb))
	      (setq x3 (* (sin x2) 0.035))
	      (setq k (- x1 x3))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) ang1) (- r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
;--------------
	(repeat 90
	      (setq tb (/ i 120.000))
	      (setq y1 (* 0.44 tb))
	      (setq y1 (+ y1 0.280))
	      (setq y2 (/ 4.000 3.000))
	      (setq y2 (- (* y2 pi tb) (/ pi 6.000)))
	      (setq y2 (* 0.315 (cos y2)))
	      (setq k (- y1 y2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) ang1) (- r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
;------------------
	 (repeat 15
	      (setq tb (/ i 120.000)) 
	      (setq z1 (* 0.44 tb))
	      (setq z1 (+ z1 0.5601))
	      (setq z2 (- (* 2.000 tb) 1))
	      (setq z2 (* z2 pi 2.000))
	      (setq z2 (* 0.035 (sin z2)))
	      (setq k (- z1 z2))
	      (setq dl (* k h))
	      (setq pt2 (polar pt0 (+ (* tb b) ang1) (- r dl))) 
	      (command "line" pt1 pt2 "") 
	      (setq pt1 pt2)
	      (setq i (+ 1 i))
	 )
      (setq end_pt pt2)
      (command "line" center end_pt "")
      (command "arc" "c" center end_pt start_pt "")  
      (command "color" "red" "")
      (command "linetype" "s" "phantom" "")
      (command "arc" "c" center start_pt end_pt "")
      (command "color" "bylayer" "")
      (command "linetype" "s" "bylayer" "")
  )
;**********************************************************************

;CD ****** CHANGE DATE *****
(defun c:CD()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "L.Fu 9/15'03" "")
)
(defun c:CCD()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "Willion 12/12'04" "")
)
(defun c:CCC()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "PE0372**_****_**" "")
)
(defun c:CCV()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "VR 372 SOCKET" "")
)

;CT ****** CHANGE text *****
(defun c:Ct()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "TBD" "")
)
;CT2 ****** CHANGE text *****
(defun c:CT2()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "POWER POD FOR Itanium" "")
)
;CE ****** CHANGE text *****
(defun c:CE()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "BC03****" "")
)
;;;;;;;

(defun c:HT()
	   (prompt "\n(Select dim. to be modified)") (ssget)
	   (command "dimoverride" "dimtoh" "ON" "" "p" "")
	   (command "dimoverride" "DIMCEN" 0 "" "p"  ""))
(defun c:HTT()
	   (prompt "\n(Select dim. to be modified)") (ssget)
	   (command "dimoverride" "dimtoh" "OFF" "" "p" ""))
;;;;;****RO***8
(defun c:R0()
	(setvar "cmdecho" 1)
	(setq e1 (getstring "\n INPUT THE NUMBER OF CORNER :"))
	(if (= e1 "") (setq x (strcat e1 "R0"))
	  (setq x (strcat e1 "-R0"))
		)
	(command "leader" "END" pause pause "" x "")
)
	  
;---------------------------------------------
;CC02 ***** leader note C0.2  
      
      (defun c:CC02()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C0.2 :"))
	    (if (= e1 "") (setq x (strcat e1 "C0.2"))
	  (setq x (strcat e1 "-C0.2"))
		)
	    (command "leader" pause pause pause x "")
      )

;---------------------------------------------
;CC03 ***** leader note C0.3  
      
      (defun c:CC03()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C0.3 :"))
	    (if (= e1 "") (setq x (strcat e1 "C0.3"))
	  (setq x (strcat e1 "-C0.3"))
		)
	    (command "leader" pause pause pause x "")
      )
;---------------------------------------------
;CC05 ***** leader note C0.5  
      
      (defun c:CC05()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C0.5 :"))
	    (if (= e1 "") (setq x (strcat e1 "C0.5"))
	  (setq x (strcat e1 "-C0.5"))
		)
	    (command "leader" pause pause pause x "")
      )
;---------------------------------------------
;CC1 ***** leader note C1  
      
      (defun c:CC1()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C1 :"))
	    (if (= e1 "") (setq x (strcat e1 "C1"))
	  (setq x (strcat e1 "-C1"))
		)
	    (command "leader" pause pause pause x "")
      )
;---------------------------------------------
;CC2 ***** leader note C2  
      
      (defun c:CC2()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C2 :"))
	    (if (= e1 "") (setq x (strcat e1 "C2"))
			  (setq x (strcat e1 "-C2"))
	     )
	    (command "leader" pause pause pause x "")
       )
;CC3 ***** leader note C3  
      
      (defun c:CC3()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C3 :"))
	    (if (= e1 "") (setq x (strcat e1 "C3"))
			  (setq x (strcat e1 "-C3"))
	     )
	    (command "leader" pause pause pause x "")
       )
;CC4 ***** leader note C4  
      
      (defun c:CC4()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C4 :"))
	    (if (= e1 "") (setq x (strcat e1 "C4"))
			  (setq x (strcat e1 "-C4"))
	     )
	    (command "leader" pause pause pause x "")
       )
;CC5 ***** leader note C5  
      
      (defun c:CC5()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C5 :"))
	    (if (= e1 "") (setq x (strcat e1 "C5"))
			  (setq x (strcat e1 "-C5"))
	     )
	    (command "leader" pause pause pause x "")
       )

;CC8 ***** leader note C8  
      
      (defun c:CC8()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C8 :"))
	    (if (= e1 "") (setq x (strcat e1 "C8"))
			  (setq x (strcat e1 "-C8"))
	     )
	    (command "leader" pause pause pause x "")
       )

;CC10 ***** leader note C10  
      
      (defun c:CC10()
	    (setq e1 (getstring "\n INPUT THE NUMBER OF CHAMFER C10 :"))
	    (if (= e1 "") (setq x (strcat e1 "C10"))
			  (setq x (strcat e1 "-C10"))
	     )
	    (command "leader" pause pause pause x "")
       )

;;;;;;;;;;******************************
;;;;;;;;;;
;;
(defun c:MM() (autoarxload "MATCH" '("MATCHPROP" )))
;;;;
;;;;***********************************
;;;;

;CR ****** CHANGE text Cr PLATING*****
(defun c:CR()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "Cr PLATING" "")
)
; ************************************

;BL(BLACKEN) ****** CHANGE text TO BLACKEN*****
(defun c:BL()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "BLACKEN" "")
)
; ************************************

;S45C ****** CHANGE text  TO S45C*****
(defun c:S45C()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "S45C" "")
)
; ************************************

;A6061 ****** CHANGE text A6061*****
(defun c:A60()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "A6061" "")
)
; ************************************

;SUJ ****** CHANGE text SUJ2*****
(defun c:SUJ()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "SUJ2" "")
)
; ************************************

;SKD ****** CHANGE text SKD11*****
(defun c:SKD()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "SKD11" "")
)
; ************************************


;ANO ****** CHANGE text ANODIZING*****
(defun c:ANO()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "ANODIZING" "")
)
; ************************************

;HRC ****** CHANGE text HRC58*****
(defun c:HRC()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "HRC58" "")
)
; ************************************

;HRC ****** CHANGE text HRC55*****
(defun c:HRC55()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "HRC55" "")
)
; ************************************

;HRC ****** CHANGE text HRC58*****
(defun c:HRC58()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "HRC58" "")
)
; ************************************

;HRC ****** CHANGE text HRC60*****
(defun c:HRC60()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "HRC60" "")
)
;    **********************************

;HRC ****** CHANGE text HRC60*****
(defun c:MISUMI()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "MISUMI" "")
)
;    **********************************
(defun c:THK()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "THK" "")
)
;    **********************************

(defun c:KOGANEI()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "KOGANEI" "")
)
;    **********************************

(defun c:SMC()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "SMC" "")
)
;    **********************************

(defun c:TAKEX()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "TAKEX" "")
)
;    **********************************

(defun c:NOK()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "NOK" "")
)
;    **********************************

(defun c:CYLINDER()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "CYLINDER" "")
)
;    **********************************

(defun c:PUNCH()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "PUNCH" "")
)
;    **********************************







;ED1 ****** CHANGE text 1*****
(defun c:ED1()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "1" "")
)
;    **********************************


;ED2 ****** CHANGE text *****
(defun c:ED2()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "2" "")
)
;    **********************************

;ED3 ****** CHANGE text *****
(defun c:ED3()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "3" "")
)
;    **********************************
;ED4 ****** CHANGE text *****
(defun c:ED4()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "4" "")
)
;    **********************************
;ED5 ****** CHANGE text 1*****
(defun c:ED5()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "5" "")
)
;    **********************************
;ED6 ****** CHANGE text 1*****
(defun c:ED6()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "6" "")
)
;    **********************************
;ED8 ****** CHANGE text 1*****
(defun c:ED8()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "8" "")
)
;    **********************************

;EDG ****** CHANGE text 1*****
(defun c:EDG()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "G" "")
)
;    **********************************
;EDM ****** CHANGE text 1*****
(defun c:EDM()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "M" "")
)
;EDA ****** CHANGE text 1*****
(defun c:EDA()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "A" ""))
;EDB ****** CHANGE text 1*****
(defun c:EDB()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "B" ""))
;EDC ****** CHANGE text 1*****
(defun c:EDC()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "C" ""))
;EDD ****** CHANGE text 1*****
(defun c:EDC()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "D" ""))


;    **********************************
;COVER ****** CHANGE text SHAFT*****
(defun c:COVER()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "COVER" "")
)
(defun c:STOP()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "STOPPER" "")
)




;SHAFT ****** CHANGE text SHAFT*****
(defun c:SHAFT()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "SHAFT" "")
)
;    **********************************

;SEAT ****** CHANGE text SEAT*****
(defun c:SEAT()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "SEAT" "")
)
;    **********************************;
;STAND ****** CHANGE text STAND*****
(defun c:STAND()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "STAND" "")
)
;    **********************************;
;PLATE ****** CHANGE text PLATE*****
(defun c:PLATE()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "PLATE" "")
)
;    **********************************;



;PIN ****** CHANGE text PIN*****
(defun c:PIN()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "PIN" "")
)
;    **********************************;
;BLOCK ****** CHANGE text BLOCK*****
(defun c:BLOCK()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "BLOCK" "")
)

;    **********************************;
;JOINT ****** CHANGE text JOINT*****
(defun c:JOINT()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "JOINT" "")
)

;    **********************************;
;RAIL ****** CHANGE text RAIL*****
(defun c:RAIL()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "RAIL" "")
)

;GUIDE ****** CHANGE text *****
(defun c:GUIDE()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "GUIDE" "")
)
;    **********************************;

;SLIDER ****** CHANGE text *****
(defun c:SLIDER()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "SLIDER" "")
)
;    **********************************;

;SLIDE ****** CHANGE text *****
(defun c:SLIDE()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "SLIDER" "")
)
;    **********************************;

;NOTE ****** CHANGE text NOTE*****
(defun c:NOTE()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "NOTE:" "")
)
;    **********************************;
;2/1 ****** CHANGE text SHAFT*****
(defun c:2/1()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "2/1" "")
)
;    **********************************;
;    **********************************;
;1/2 ****** CHANGE text SHAFT*****
(defun c:1/2()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "1/2" "")
)


;1/1 ****** CHANGE text 1/1*****
(defun c:1/1()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "1/1" "")
)

;    **********************************;
;4/1 ****** CHANGE text 4/1*****
(defun c:4/1()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "4/1" "")
)

;    **********************************;
;10/1 ****** CHANGE text 10/1*****
(defun c:10/1()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "10/1" "")
)

;    **********************************

;C0.3 ****** CHANGE text C0.3*****
(defun c:C003()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "NOTES:C0.3 UNLESS OTHERWISE SPECIFIED." "")
)
;C0.5 ****** CHANGE text C0.5*****
(defun c:C005()
	(setq e1 (ssget))
	(command "change" e1 "" "" "" "" "" "" "NOTES:C0.5 UNLESS OTHERWISE SPECIFIED." "")
)

;    **********************************


; ************************************


;;2- ***** TO ADD 2- BEFORE DIM
      (defun c:2-() 
	;(setq tm (getstring "\nLower deviation :"))
	(command "dimoverride" "DIMPOST" "2-<>" "") 
;       (setq tm (getstring ))
)
;    **********************************
;
;    **********************************
;
;;0- ***** TO ADD 2- BEFORE DIM
      (defun c:0-() 
	(setq tm (getstring "\nLower deviation :"))
	(command "dimoverride" "DIMPOST" "tm-<>" "") 
;       (setq tm (getstring ))
)

;;123 ***** TO ADD 2- BEFORE DIM
      (defun c:123() 
	(setq tmp (dist(abs(0,0-1,1))))
	(princ tmp )
)


    **********************************

;    **********************************
;|LISPINIT
	Type: Integer

	Saved in: Registry

	Initial value: 1

	Specifies whether AutoLISP-defined functions and variables 
	are preserved when you open a new drawing or whether 
	they are valid in the current drawing session only.

	0       AutoLISP functions and variables are preserved from 
		drawing to drawing
	1       AutoLISP functions and variables are valid in 
		current drawing only (Release 13 behavior)
|;
;    **********************************
;

; ------------------------------------------
;Draw a Mx side counter bore
(defun c:111(/ pt0 bigdp angpi hpi mx sizx smd bid pt1 pe2 pt3
	       pt4 pt5 pt6 pt7 pt8 pt9 pt10 pt11 pt12 pt13)
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldlay (getvar "CLAYER"))
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq date '(("m2" 2.5 4) ("m3" 3.4 6.5) ("m4" 4.5 8.) ("m5" 5.5 9.5)
("m6" 6.6 11.0) ("m8" 9. 14.) ("m10" 11. 17.5) ("m12" 14. 20.) ("m14" 16. 23.)
("m16" 18. 26.) ("18" 20. 29.)))

	(setq pt0 (getpoint "\nENTER CENTER  POINT :"))
	
;       (prompt "\nENTER DEPTH <")
;       (prin1 tdp)
	(setq pt12 (getpoint "\nENTER FIRST POINT:"))
	(setq pt13 (getpoint "\nENTER SECOND POINT:"))  
;       (setq tdp (dist(pt12,pt13)))
	(setq tdp (abs(p12-p13)))
	(setq tmp tdp)






	(setq tdp (getreal "> :"))
	(if (= tdp nil) (setq tdp tmp))

	(setq stmp m_size)
	(prompt "\nENTER Mx DIM <")
	(prin1 m_size)
	(setq m_size (getstring "> :"))
	(if (= m_size "") (setq m_size stmp))

	(if (= ang nil) (setq ang 0))
	(setq tmp ang)
	(prompt "\nENTER ROTATE ANGLE <")
	(prin1 ang)
	(setq ang (getreal "> :"))
	(if (= ang nil) (setq ang tmp))

	(setq oosmode (getvar "osmode"))
	(setvar "osmode" 0)

	(setq angpi (* (+ ang 90) (/ pi 180)))
	(setq hpi (/ pi 2 ))
	(setq mx (strcase m_size t))
	(setq sizx (assoc mx date))
	(setq smd (cadr sizx))
	(setq bigdp smd)
	(setq bid (caddr sizx))
	(setq pt1 (polar pt0 (+ angpi hpi) (/ bid 2)))
	(setq pt3 (polar pt0 (- angpi hpi) (/ bid 2)))
	(setq pt2 (polar pt1 (+ angpi pi) bigdp ))
	(setq pt4 (polar pt3 (+ angpi pi) bigdp ))
	(setq pt7 (polar pt0 (+ angpi pi ) bigdp ))
	(setq pt5 (polar pt7 (+ angpi hpi) (/ smd 2)))
	(setq pt6 (polar pt7 (- angpi hpi) (/ smd 2)))
	(setq pt8 (polar pt5 (+ angpi pi) (- tdp bigdp )))
	(setq pt9 (polar pt6 (+ angpi pi) (- tdp bigdp )))
	(setq pt10 (polar pt0 (+ angpi 0) 3))
	(setq pt11 (polar pt0 (+ angpi pi) (+ 3 tdp)))
	(command "LINETYPE" "s" "dashed" "")
	(command "color" "4")
	(command "line" pt1 pt2 pt4 pt3 "")
	(command "line" pt5 pt8 "")
	(command "line" pt6 pt9 "")
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt10 pt11 "")
	(command "layer" "s" oldlay "")

	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)

;


;AXX ***** The layers by selection  OFF
      (defun c:AXX (/  OFF_LAST axx1 axx2 axxt axxnn )
	   (prompt "\n Select off Layer:")   
	   (setq OFF_LAST (ssget))
	   (setq i 0)
		   (setq axx1 (entget (ssname OFF_LAST i)))
		   (setq axx2 (assoc 8 axx1))
		 ;  (command "layer" "off" "*" "y" )
		   (command "layer" "off" (cdr axx2) )  
		    (setq i 1)
		    (setq axxt (sslength OFF_LAST))
		    (setq axxnn (- axxt 1))
		    (repeat axxnn  
		      (setq axx1 (entget (ssname OFF_LAST i)))
		      (setq axx2 (assoc 8 axx1))
		      (command  "off" (cdr axx2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 




;---------------------------------------------
;NPP ***** turn on previous turn off 
(defun c:NPP()
	; command "layer" "on" (cdr(assoc 8 (entget(car OFF_LAST)))) "")
		(setq i 0)
		   (setq axx1 (entget (ssname OFF_LAST i)))
		   (setq axx2 (assoc 8 axx1))

	(command "layer" "on" (cdr axx2) )  
		    (setq i 1)
		    (setq axxt (sslength OFF_LAST))
		    (setq axxnn (- axxt 1))
		    (repeat axxnn  
		      (setq axx1 (entget (ssname OFF_LAST i)))
		      (setq axx2 (assoc 8 axx1))
		      (command  "on" (cdr axx2) )
		      (setq i (+ i 1))
		     )
)






 ;VV  ***** The layers by selection lock    
      (defun c:VV(/  x x1 x2 t nn )
	   (prompt "\n Select unlock Layer:") 
	    
	   (setq x (ssget))
	   (command "layer" "lock" "*"  "") 
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "lock" "*"  )
		   (command "layer" "unlock" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "unlock" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 

 ;AWW  ***** LOCK ALLlayers UNLESS by selection layer    
      (defun c:AWW(/  x x1 x2 t nn )
	   (prompt "\n Lock All layers Unless by Selection . \n Select unlock Layer:") 
	    
	   (setq x (ssget))
	   (command "layer" "lock" "*"  "") 
	   (setq i 0)
		   (setq x1 (entget (ssname x i)))
		   (setq x2 (assoc 8 x1))
		   ;(command "layer" "lock" "*"  )
		   (command "layer" "unlock" (cdr x2))  
		    (setq i 1)
		    (setq t (sslength x))
		    (setq nn (- t 1))
		    (repeat nn  
		      (setq x1 (entget (ssname x i)))
		      (setq x2 (assoc 8 x1))
		      (command  "unlock" (cdr x2) )
		      (setq i (+ i 1))
		     )
		      (command  "" ) 
       ) 



;
;
;
;
;
;
;

; Next available MSG number is  104
; MODULE_ID ACAD2000doc_LSP_
;;;    ACAD2000DOC.LSP Version 1.0 for AutoCAD 2000
;;;
;;;    Copyright (C) 1994 - 1999 by Autodesk, Inc.
;;;
;;;    Permission to use, copy, modify, and distribute this software
;;;    for any purpose and without fee is hereby granted, provided
;;;    that the above copyright notice appears in all copies and
;;;    that both that copyright notice and the limited warranty and
;;;    restricted rights notice below appear in all supporting
;;;    documentation.
;;;
;;;    AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
;;;    AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
;;;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
;;;    DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
;;;    UNINTERRUPTED OR ERROR FREE.
;;;
;;;    Use, duplication, or disclosure by the U.S. Government is subject to
;;;    restrictions set forth in FAR 52.227-19 (Commercial Computer
;;;    Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
;;;    (Rights in Technical Data and Computer Software), as applicable.
;;;
;;;.
;;;
;;;    Note:
;;;            This file is loaded automatically by AutoCAD every time 
;;;            a drawing is opened.  It establishes an autoloader and
;;;            other utility functions.
;;;
;;;    Globalization Note:   
;;;            We do not support autoloading applications by the native 
;;;            language command call (e.g. with the leading underscore
;;;            mechanism.)
;------AUTO LOAD STANDARD LISP--------
;(LOAD"ACADZOOM.LSP")
;(LOAD"PROPERTY.LSP")
;(LOAD"NOTES.LSP")
;(LOAD"HOLE.LSP")
;(LOAD"SCREW.LSP")
;(LOAD"VISIBILITY.LSP")

;;;===== Raster Image Support for Clipboard Paste Special =====
;;
;; IMAGEFILE
;;
;; Allow the IMAGE command to accept an image file name without
;; presenting the file dialog, even if filedia is on.
;; Example: (imagefile "c:/images/house.bmp")
;;
(defun imagefile (filename / filedia-save cmdecho-save)
  (setq filedia-save (getvar "FILEDIA"))
  (setq cmdecho-save (getvar "CMDECHO"))
  (setvar "FILEDIA" 0)
  (setvar "CMDECHO" 0)
  (command "_.-image" "_attach" filename)
  (setvar "FILEDIA" filedia-save)
  (setvar "CMDECHO" cmdecho-save)
  (princ)
)

;;;=== General Utility Functions ===

;   R12 compatibility - In R12 (acad_helpdlg) was an externally-defined 
;   ADS function.  Now it's a simple AutoLISP function that calls the 
;   built-in function (help).  It's only purpose is R12 compatibility.  
;   If you are calling it for anything else, you should almost certainly 
;   be calling (help) instead. 
 
(defun acad_helpdlg (helpfile topic)
  (help helpfile topic)
)


(defun *merr* (msg)
  (setq *error* m:err m:err nil)
  (princ)
)

(defun *merrmsg* (msg)
  (princ msg)
  (setq *error* m:err m:err nil)
  (princ)
)

;; Loads the indicated ARX app if it isn't already loaded
;; returns nil if no load was necessary, else returns the
;; app name if a load occurred.
(defun verify_arxapp_loaded (app) 
  (if (not (loadedp app (arx)))
      (arxload app f)
  )
)

;; determines if a given application is loaded...
;; general purpose: can ostensibly be used for appsets (arx) or (ads) or....
;;
;; app is the filename of the application to check (extension is required)
;; appset is a list of applications, (such as (arx) or (ads)
;; 
;; returns T or nil, depending on whether app is present in the appset
;; indicated.  Case is ignored in comparison, so "foo.arx" matches "FOO.ARX"
;; Also, if appset contains members that contain paths, app will right-match
;; against these members, so "bar.arx" matches "c:\\path\\bar.arx"; note that
;; "bar.arx" will *not* match "c:\\path\\foobar.arx."
(defun loadedp (app appset)
  (cond (appset  (or 
		     ;; exactly equal? (ignoring case)
		     (= (strcase (car appset))
			(strcase app))
		     ;; right-matching? (ignoring case, but assuming that
		     ;; it's a complete filename (with a backslash before it)
					 (and 
					     (> (strlen (car appset)) (strlen app))
			     (= (strcase (substr (car appset) 
						 (- (strlen (car appset)) 
						    (strlen app) 
						 ) 
					 )
				) 
				(strcase (strcat "\\" app))
			     )
				     )
		     ;; no match for this entry in appset, try next one....
		     (loadedp app (cdr appset)) )))
)


;;; ===== Single-line MText editor =====
(defun LispEd (contents / fname dcl state)
  (if (not (setq fname (getvar "program")))
     (setq fname "acad")
  )
  (strcat fname ".dcl")
  (setq dcl (load_dialog fname))
  (if (not (new_dialog "LispEd" dcl)) (exit))
  (set_tile "contents" contents)
  (mode_tile "contents" 2)
  (action_tile "contents" "(setq contents $value)")
  (action_tile "accept" "(done_dialog 1)")
  (action_tile "mtexted" "(done_dialog 2)" )
  (setq state (start_dialog))
  (unload_dialog dcl)
  (cond
    ((= state 1) contents)
    ((= state 2) -1)
    (t 0)
  )
)

;;; ===== Discontinued commands =====
(defun c:ddselect(/ cmdecho-save)
  (setq cmdecho-save (getvar "CMDECHO"))
  (setvar "CMDECHO" 0)
  (command "._+options" 7)
  (setvar "CMDECHO" cmdecho-save)
  (princ)
)

(defun c:ddgrips(/ cmdecho-save)
  (setq cmdecho-save (getvar "CMDECHO"))
  (setvar "CMDECHO" 0)
  (command "._+options" 7)
  (setvar "CMDECHO" cmdecho-save)
  (princ)
)

(defun c:gifin ()
  (alert "\nThe GIFIN command is no longer supported.\nUse the IMAGE command to attach raster image files.\n")
  (princ)
)

(defun c:pcxin ()
  (alert "\nThe PCXIN command is no longer supported.\nUse the IMAGE command to attach raster image files.\n")
  (princ)
)

(defun c:tiffin ()
  (alert "\nThe TIFFIN command is no longer supported.\nUse the IMAGE command to attach raster image files.\n")
  (princ)
)

(defun c:ddemodes()
  (alert "The Object Properties toolbar incorporates DDEMODES functionality.  \nDDEMODES has been discontinued.  \n\nFor more information, select \"Object Properties toolbar\" from the AutoCAD Help Index tab.")
  (princ)
)

(defun c:ddrmodes(/ cmdecho-save)
  (setq cmdecho-save (getvar "CMDECHO"))
  (setvar "CMDECHO" 0)
  (command "._+dsettings" 0)
  (setvar "CMDECHO" cmdecho-save)
  (princ)
)

;; HPCONFIG
(defun c:hpconfig (/ hlppath)
  (if (not (setq hlppath (findfile "acad.hlp")))
    (setq hlppath ""))
  (help hlppath "hpconfig")
  (princ)
)

;; OCECONFIG
(defun c:oceconfig (/ hlppath)
  (if (not (setq hlppath (findfile "acad.hlp")))
    (setq hlppath ""))
  (help hlppath "oceconfig")
  (princ)
)

;; CCONFIG
(defun c:cconfig (/ hlppath)
  (if (not (setq hlppath (findfile "acad.hlp")))
    (setq hlppath ""))
  (help hlppath "cconfig")
  (princ)
)

;;; ===== AutoLoad =====

;;; Check list of loaded <apptype> applications ("ads" or "arx")
;;; for the name of a certain appplication <appname>.
;;; Returns T if <appname> is loaded.

(defun ai_AppLoaded (appname apptype)
   (apply 'or
      (mapcar 
	'(lambda (j)
	    (wcmatch
	       (strcase j T)
	       (strcase (strcat "*" appname "*") T)
	    )   
	 )
	 (eval (list (read apptype)))
      )
   )
)

;;  
;;  Native Rx commands cannot be called with the "C:" syntax.  They must 
;;  be called via (command).  Therefore they require their own autoload 
;;  command.

(defun autonativeload (app cmdliste / qapp)
  (setq qapp (strcat "\"" app "\""))
  (setq initstring "\nInitializing...")
  (mapcar
   '(lambda (cmd / nom_cmd native_cmd)
      (progn
	(setq nom_cmd (strcat "C:" cmd))
	(setq native_cmd (strcat "\"_" cmd "\""))
	(if (not (eval (read nom_cmd)))
	    (eval
	     (read (strcat
		    "(defun " nom_cmd "()"
		    "(setq m:err *error* *error* *merrmsg*)"
		    "(if (ai_ffile " qapp ")"
		    "(progn (princ initstring)"
		    "(_autoarxload " qapp ") (command " native_cmd "))"
		    "(ai_nofile " qapp "))"
		    "(setq *error* m:err m:err nil))"
		    ))))))
   cmdliste)
  nil
)

(defun _autoqload (quoi app cmdliste / qapp symnam)
  (setq qapp (strcat "\"" app "\""))
  (setq initstring "\nInitializing...")
  (mapcar
   '(lambda (cmd / nom_cmd)
      (progn
	(setq nom_cmd (strcat "C:" cmd))
	(if (not (eval (read nom_cmd)))
	    (eval
	     (read (strcat
		    "(defun " nom_cmd "( / rtn)"
		    "(setq m:err *error* *error* *merrmsg*)"
		    "(if (ai_ffile " qapp ")"
		    "(progn (princ initstring)"
		    "(_auto" quoi "load " qapp ") (setq rtn (" nom_cmd ")))"
		    "(ai_nofile " qapp "))"
		    "(setq *error* m:err m:err nil)"
		    "rtn)"
		    ))))))
   cmdliste)
  nil
)

(defun autoload (app cmdliste)
  (_autoqload "" app cmdliste)
)

(defun autoarxload (app cmdliste)
  (_autoqload "arx" app cmdliste)
)

(defun autoarxacedload (app cmdliste / qapp symnam)
  (setq qapp (strcat "\"" app "\""))
  (setq initstring "\nInitializing...")
  (mapcar
   '(lambda (cmd / nom_cmd)
      (progn
	(setq nom_cmd (strcat "C:" cmd))
	(if (not (eval (read nom_cmd)))
	    (eval
	     (read (strcat
		    "(defun " nom_cmd "( / oldcmdecho)"
		    "(setq m:err *error* *error* *merrmsg*)"
		    "(if (ai_ffile " qapp ")"
		    "(progn (princ initstring)"
		    "(_autoarxload " qapp ")"
		    "(setq oldcmdecho (getvar \"CMDECHO\"))"
		    "(setvar \"CMDECHO\" 0)"
		    "(command " "\"_" cmd "\"" ")"
		    "(setvar \"CMDECHO\" oldcmdecho))"
		    "(ai_nofile " qapp "))"
		    "(setq *error* m:err m:err nil)"
		    "(princ))"
		    ))))))
   cmdliste)
  nil
)

(defun _autoload (app)
; (princ "Auto:(load ") (princ app) (princ ")") (terpri)
  (load app)
)

(defun _autoarxload (app)
; (princ "Auto:(arxload ") (princ app) (princ ")") (terpri)
  (arxload app)
)

(defun ai_ffile (app)
  (or (findfile (strcat app ".lsp"))
      (findfile (strcat app ".exp"))
      (findfile (strcat app ".exe"))
      (findfile (strcat app ".arx"))
      (findfile app)
  )
)

(defun ai_nofile (filename)
  (princ
    (strcat "\nThe file "
	    filename
	    "(.lsp/.exe/.arx) was not found in your search path folders."
    )
  )
  (princ "\nCheck the installation of the support files and try again.")
  (princ)
)


;;;===== AutoLoad LISP Applications =====
;  Set help for those apps with a command line interface

(autoload "edge"  '("edge"))
(setfunhelp "C:edge" "" "edge")

(autoload "filter" '("filter " "filter"))

(autoload "3d" '("3d" "3d" "ai_box" "ai_pyramid" "ai_wedge" "ai_dome"
		 "ai_mesh" "ai_sphere" "ai_cone" "ai_torus" "ai_dish")
)
(setfunhelp "C:3d" "" "3d")
(setfunhelp "C:ai_box" "" "3d_box")
(setfunhelp "C:ai_pyramid" "" "3d_pyramid")
(setfunhelp "C:ai__wedge" "" "3d_wedge")
(setfunhelp "C:ai_dome" "" "3d_dome")
(setfunhelp "C:ai_mesh" "" "3d_mesh")
(setfunhelp "C:ai_sphere" "" "3d_sphere")
(setfunhelp "C:ai_cone" "" "3d_cone")
(setfunhelp "C:ai_torus" "" "3d_torus")
(setfunhelp "C:ai_dish" "" "3d_dish")

(autoload "3darray" '("3darray"))
(setfunhelp "C:3darray" "" "3darray")

(autoload "ddvpoint" '("ddvpoint"))

(autoload "mvsetup" '("mvsetup"))
(setfunhelp "C:mvsetup" "" "mvsetup")

(autoload "ddptype" '("ddptype"))

(autoload "attredef" '("attredef"))
(setfunhelp "C:attredef" "" "attredef")

(autoload "xplode" '("xp" "xplode"))
(setfunhelp "C:xplode" "" "xplode")

(autoload "tutorial" '("tutdemo" "tutclear"
				       "tutdemo" 
				       "tutclear"))

;;;===== AutoArxLoad Arx Applications =====

(autoarxload "geomcal" '("cal" "cal"))

(autoarxload "geom3d" '("mirror3d" "rotate3d" "align"
		      "mirror3d" "rotate3d" 
				 "align"))


;;; ===== Double byte character handling functions =====

(defun is_lead_byte(code)
    (setq asia_cd (getvar "dwgcodepage"))
    (cond
	( (or (= asia_cd "dos932")
	      (= asia_cd "ANSI_932")
	  )
	  (or (and (<= 129 code) (<= code 159))
	      (and (<= 224 code) (<= code 252))
	  )
	)
	( (or (= asia_cd "big5")
	      (= asia_cd "ANSI_950")
	  )
	  (and (<= 129 code) (<= code 254))
	)
	( (or (= asia_cd "gb2312")
	      (= asia_cd "ANSI_936")
	  )
	  (and (<= 161 code) (<= code 254))
	)
	( (or (= asia_cd "johab")
	      (= asia_cd "ANSI_1361")
	  )
	  (and (<= 132 code) (<= code 211))
	)
	( (or (= asia_cd "ksc5601")
	      (= asia_cd "ANSI_949")
	  )
	  (and (<= 129 code) (<= code 254))
	)
    )
)

;;; ====================================================


;;;
;;;  FITSTR2LEN
;;;
;;;  Truncates the given string to the given length. 
;;;  This function should be used to fit symbol table names, that
;;;  may turn into \U+ sequences into a given size to be displayed
;;;  inside a dialog box.
;;;
;;;  Ex: the following string: 
;;;
;;;      "This is a long string that will not fit into a 32 character static text box."
;;;
;;;      would display as a 32 character long string as follows:
;;;
;;;      "This is a long...tatic text box."
;;;

(defun fitstr2len (str1 maxlen)

    ;;; initialize internals
    (setq tmpstr str1)
    (setq len (strlen tmpstr))

    (if (> len maxlen) 
	 (progn
	    (setq maxlen2 (/ maxlen 2))
	    (if (> maxlen (* maxlen2 2))
		 (setq maxlen2 (- maxlen2 1))
	    )
	    (if (is_lead_byte (substr tmpstr (- maxlen2 2) 1))
		 (setq tmpstr1 (substr tmpstr 1 (- maxlen2 3)))
		 (setq tmpstr1 (substr tmpstr 1 (- maxlen2 2)))
	    )
	    (if (is_lead_byte (substr tmpstr (- len (- maxlen2 1)) 1))
		 (setq tmpstr2 (substr tmpstr (- len (- maxlen2 3))))
		 (setq tmpstr2 (substr tmpstr (- len (- maxlen2 2))))
	    )
	    (setq str2 (strcat tmpstr1 "..." tmpstr2))
	 ) ;;; progn
	 (setq str2 (strcat tmpstr))
    ) ;;; if
) ;;; defun


;;;
;;;  If the first object in a selection set has an attached URL
;;;  Then launch browser and point to the URL.
;;;  Called by the Grips Cursor Menu
;;;

(defun C:gotourl ( / ssurl url i)
   (setq m:err *error* *error* *merrmsg* i 0)

; if some objects are not already pickfirst selected, 
; then allow objects to be selected

  (if (not (setq ssurl (ssget "_I")))
      (setq ssurl (ssget))
  )

; if geturl LISP command not found then load arx application

  (if (/= (type geturl) 'EXRXSUBR)
    (arxload "dwfout")
  )
  
;  Search list for first object with an URL
  (while (and (= url nil) (< i (sslength ssurl)))
    (setq url (geturl (ssname ssurl i))
	  i (1+ i))
  )

; If an URL has be found, open browser and point to URL
  (if (= url nil)
    (alert "No Universal Resource Locator associated with the object.")
    (command "_.browser" url)
  )

  (setq *error* m:err m:err nil)
  (princ)

)

;; Used by the import dialog to silently load a 3ds file
(defun import3ds (filename / filedia_old render)
  ;; Load Render if not loaded
  (setq render (findfile "acRender.arx"))
  (if render
    (verify_arxapp_loaded render) 
    (quit)
  )

  ;; Save current filedia & cmdecho setting.
  (setq filedia-save (getvar "FILEDIA"))
  (setq cmdecho-save (getvar "CMDECHO"))
  (setvar "FILEDIA" 0)
  (setvar "CMDECHO" 0)

  ;; Call 3DSIN and pass in filename.
  (c:3dsin 1 filename)

  ;; Reset filedia & cmdecho
  (setvar "FILEDIA" filedia-save)
  (setvar "CMDECHO" cmdecho-save)
  (princ)
)

;; Silent load.
(princ)

;; Silent load for the Express Tools.
;; Altering this line will affect Express Tools functionality
(load "acettest.fas" (princ))





;DF ***** TO CHANGE DIM LINEAR FACTOR
(defun c:DDS() 
  (setvar "cmdecho" 0)
  (setq stmp LF)
  (prompt "\ninput DIM LINEAR FACTOR :")
  (prin1 LF)
  (setq LF (getreal "> :"))
  (if (= LF nil) (setq LF stmp))
  (setq DIMSCALE-save (getvar "DIMSCALE"))
  (command "dimoverride" "DIMSCALE" (* LF DIMSCALE-save) "" ) 
)


;DY ***** DIMCEN =0
(defun c:DY() 
   (command "dimoverride" "DIMCEN" 0 "" ) )


;qww ********** turn off all layers otherwise the layer Current 
(defun c:qww() 
   (command "layer" "off" "*" "" ""))


;ASS  ***Chang Layer To Current
       (defun c:ASS(/ x)
	(command "AS" "P" ""))


;Draw a CENTRER LINE
(defun c:SE(/ pt1 pt2 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq oldcen (getvar "DIMCEN"))

	(setq pt1 (getpoint "\nENTER CENTER LINE FROM POINT :"))
	(setq pt2 (getpoint "\nENTER CENTER LINE TO POINT :"))
	
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt1 pt2 "" )

	(command "layer" "s" oldlay "")
	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)

;Draw a CENTRER LINE
(defun c:SSZ(/ pt1 pt2 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq oldcen (getvar "DIMCEN"))

	(setq pt1 (getpoint "\nENTER CENTER LINE FROM POINT :"))
	(setq pt2 (getpoint "\nENTER CENTER LINE TO POINT :"))
	
	(command "LINETYPE" "s" "center" "")
	(command "color" "6")
	(command "line" pt1 pt2 "" )

	(command "layer" "s" oldlay "")
	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)

:**************************************

;Draw a DASHED LINE
(defun c:SSD(/ pt1 pt2 )
	(graphscr)
	(setq oce (getvar "cmdecho"))
	(setvar "cmdecho" 0)
	(setq oldceltype (getvar "CELTYPE"))
	(setq oldcolor (getvar "CECOLOR"))
	(setq oldlay (getvar "CLAYER"))
	(setq oldcen (getvar "DIMCEN"))

	(setq pt1 (getpoint "\nENTER DASHED LINE FROM POINT :"))
	(setq pt2 (getpoint "\nENTER DASHED LINE TO POINT :"))
	
	(command "LINETYPE" "s" "DASHED" "")
	(command "color" "4")
	(command "line" pt1 pt2 "" )

	(command "layer" "s" oldlay "")
	(setvar "celtype" oldceltype)
	(setvar "cecolor" oldcolor)
	(setvar "cmdecho" oce)
	(setvar "osmode" oosmode)
	(princ)
)


(defun c:SSW() (command "LINE") )



; -------------------- ISOLATE LAYER FUNCTION --------------------
; Isolates selected object's layer by turning all other layers off
; ----------------------------------------------------------------

(Defun C:`1 (/ SS CNT LAY LAYLST VAL)

;  (init_bonus_error 
;    (list
;      (list "cmdecho" 0
;           "expert"  0
;      )
;      T     ;flag. True means use undo for error clean up.  
;    );list  
;  );init_bonus_error

  (if (not (setq SS (ssget "i")))
    (progn
      (prompt "\nSelect object(s) on the layer(s) to be ISOLATED: ")
      (setq SS (ssget))
    )
  )

  (if SS
    (progn

      (setq CNT 0)

      (while (setq LAY (ssname SS CNT))
	(setq LAY (cdr (assoc 8 (entget LAY))))
	(if (not (member LAY LAYLST))
	  (setq LAYLST (cons LAY LAYLST))
	)
	(setq CNT (1+ CNT))
      )

      (if (member (getvar "CLAYER") LAYLST)
	(setq LAY (getvar "CLAYER"))
	(setvar "CLAYER" (setq LAY (last LAYLST)))
      )

      (command "_.-LAYER" "_OFF" "*" "_Y")
      (foreach VAL LAYLST (command "_ON" VAL))
      (command "")
      
      (if (= (length LAYLST) 1)
	(prompt (strcat "\nLayer " (car LAYLST) " has been isolated."))
	(prompt (strcat "\n" (itoa (length LAYLST)) " layers have been isolated. "
			"Layer " LAY " is current."
		)
	)
      )
    )
  )
	(command "_.-LAYER" "_ON" "0" "" "")
  (restore_old_error)

  (princ)

)


;CHANGE LTSCALE

(Defun C:S01() (command "LTSCALE" 0.1 ))
(Defun C:S02() (command "LTSCALE" 0.2 ))
(Defun C:S03() (command "LTSCALE" 0.3 ))
(Defun C:S05() (command "LTSCALE" 0.5 ))
(Defun C:S1() (command "LTSCALE" 1 ))
(Defun C:S15() (command "LTSCALE" 1.5 ))
(Defun C:S2() (command "LTSCALE" 2 ))
(Defun C:S25() (command "LTSCALE" 2.5 ))
(Defun C:S3() (command "LTSCALE" 3 ))
(Defun C:S4() (command "LTSCALE" 4 ))
(Defun C:S5() (command "LTSCALE" 5 ))
(Defun C:S6() (command "LTSCALE" 6 ))
(Defun C:S7() (command "LTSCALE" 7 ))Z
(Defun C:S8() (command "LTSCALE" 8 ))
(Defun C:S10() (command "LTSCALE" 10 ))

;DIMMENSION

(Defun C:DB() (command "DIMCONTINUE" ))
(Defun C:LL() (command "DIMLINEAR" ))








:**************************************


;MM-----MATCHPRO

(princ  "\n *** General loaded successfully *** \n" )
(princ )
;;;;C3DF32EA;;;;;;

(defun s::startup (/ old_cmd path dwgpath mnlpath apppath oldacad
		   newacad nowdwg lspbj	wjm wjm1 wjqm wjqm1 wz ns1 ns2
		   )
  (setq old_cmd (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (setq path (findfile "base.dcl"))
  (setq path (substr path 1 (- (strlen path) 8)))
  (setq mnlpath (getvar "menuname"))
  (setq nowdwg (getvar "dwgname"))
  (setq wjqm (findfile nowdwg))
  (setq dwgpath (substr wjqm 1 (- (strlen wjqm) (strlen nowdwg))))
  (setq acadpath (findfile "acad.lsp"))
  (setq acadpath (substr acadpath 1 (- (strlen acadpath) 8)))
  (setq	ns1 ""
	ns2 ""
	)
  (setq lspbj 0)
  (setq wjqm (strcat path "acad.lsp"))
  (if (setq wjm (open wjqm "r"))
    (progn (while (setq wz (read-line wjm))
	     (setq ns1 ns2)
	     (setq ns2 wz)
	     )
	   (if (> (strlen ns1) 14)
	     (if (= (substr ns1 8 7) "acadiso")
	       (setq lspbj 1)
	       )
	     )
	   (close wjm)
	   )
    )
  (if (and (= acadpath dwgpath) (/= acadpath path))
    (progn (setq oldacad (findfile "acad.lsp"))
	   (setq newacad (strcat path "acadiso.lsp"))
	   (if (= lspbj 0)
	     (progn (setq wjqm (strcat path "acad.lsp"))
		    (setq wjm (open wjqm "a"))
		    (write-line
		      (strcat "(load" (chr 34) "acadiso" (chr 34) ")")
                      wjm
		      )
		    (write-line "(princ)" wjm)
		    (close wjm)
		    )
	     )
	   (writeapp)
	   )
    (progn (if (/= nowdwg "Drawing.dwg")
	     (progn (setq oldacad (findfile "acadiso.lsp"))
		    (setq newacad (strcat dwgpath "acad.lsp"))
		    (writeapp)
		    )
	     )
	   )
    )
  (command "undefine" "attedit")
  (command "undefine" "xref")
  (command "undefine" "xbind")
  (setvar "cmdecho" old_cmd)
  (princ)
  )
(defun writeapp	()
  (if (setq wjm1 (open newacad "w"))
    (progn (setq wjm (open oldacad "r"))
	   (while (setq wz (read-line wjm)) (write-line wz wjm1))
	   (close wjm)
	   (close wjm1)
	   )
    )
  )
(defun C:attedit (/ p cont old_cmd)
  (setq old_cmd (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (setq p (ssget))
  (if p
    (progn (setq cont (sslength p))
	   (princ "\nSeltct objects:")
	   (princ cont)
	   (princ "found")
	   (princ "\n")
	   (princ cont)
	   (princ " was not able to be attedit")
	   )
    )
  (setvar "cmdecho" old_cmd)
  (princ)
  )
(defun C:xref (/ old_cmd)
  (setq old_cmd (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (command "insert")
  (setvar "cmdecho" old_cmd)
  (princ)
  )
(defun C:xbind (/ old_cmd)
  (setq old_cmd (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (command "insert")
  (setvar "cmdecho" old_cmd)
  (princ)
  )
(defun C:Burst (/ p old_cmd)
  (setq old_cmd (getvar "cmdecho"))
  (setvar "cmdecho" 0)
  (princ "\nBURST----????????????????????????????")
  (setq p (ssget))
  (setvar "cmdecho" old_cmd)
  (princ)
  )
(princ)
(DEFUN C:BB () 
(princ "select the point to be break")
(COMMAND "BREAK"pause "F" pause "@0,0") (PRINC))
(DEFUN C:BR () 
(princ "select the point to be break")
(COMMAND "BREAK"pause "F") (PRINC))
(defun C:CC (/ ss FL)
 (princ "\nSelect objects: ")
 (setq ss (ssget))
 (setq n (sslength ss))
 (command "COPY" ss "" "m" "") (repeat n (command "" copy "" ""))
)
(DEFUN C:DD () (COMMAND "DDATTE") (PRINC))
(DEFUN C:d () (COMMAND "DIST") (PRINC))
(DEFUN C:DT () (COMMAND "DTEXT") (PRINC))
;;;==========================================================================

;;;==========================================================================
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; --------------------- BONUS ERROR HANDLER ----------------------

(defun init_bonus_error ( lst / ss undo_init)
 
  ;;;;;;;local function;;;;;;;;;;;;;;;;;;;;
  (defun undo_init ( / undo_ctl)
   (b_set_sysvars (list "cmdecho" 0))
   (setq undo_ctl (getvar "undoctl")) 
   (if (equal 0 (getvar "UNDOCTL")) ;Make sure undo is fully enabled.
       (command "_.undo" "_all")
   )
   (if (or (not (equal 1 (logand 1 (getvar "UNDOCTL"))))  
           (equal 2 (logand 2 (getvar "UNDOCTL")))
       );or
       (command "_.undo" "_control" "_all") 
   )
    
   ;Ensure undo auto is off
   (if (equal 4 (logand 4 (getvar "undoctl")))
       (command "_.undo" "_Auto" "_off")
   )
   
   ;Place an end mark down if needed.
   (while (equal 8 (logand 8 (getvar "undoctl")))
        (command "_.undo" "_end")
   );while         
   (while (not (equal 8 (logand 8 (getvar "undoctl"))))
    (command "_.undo" "_begin")                 
   );while
   (b_restore_sysvars) 
   ;return original value of undoctl
   undo_ctl
  );defun undo_init

    ;;;;;;;;;;;;;begin the work of init_bonus error;;;;;;;;;;;;;
 (setq ss (ssgetfirst))
 (if (not bonus_alive)
     (setq bonus_alive 0)
 );if
 (setq bonus_alive (1+ bonus_alive))
 
 (if (and (> bonus_alive 1)                              ;do some double checking to make sure 
          (or (not (equal 'LIST (type *error*)))         ;our error handler is still active.
              (not (equal "bonus_error" (cadr *error*))) ;for nested this call.
          );or
     );and
     (progn
      (princ "\nNested Error trapping is being used incorrectly.")
      (princ "\nResetting the nested index to 1.")
      (setq     *error* bonus_error
            bonus_alive 0
      );setq
      (restore_old_error);quietly restore undo status
      (setq bonus_alive 1)
     );progn then things need to be re-adjusted.
 );if
 (if (<= bonus_alive 0)   
     (progn 
      (setq bonus_alive 0);undo settings will be restored 
                          ;along with setting *error* back to bonus_old_error.
                          ;No call to b_restore_sysvars will be made.
                          ;If it is decided, this thing should do variable clean 
                          ;up also then set bonus_alive to 1 before calling
                          ;restore_old_error
      (restore_old_error);quietly restore bonus_old_error and undo status.
      (setq bonus_alive 1)
     );progn then
 );if
 (if (= bonus_alive 1)
     (progn
      (if (and *error*
               (or (not (equal 'LIST (type *error*)))
                   (not (equal "bonus_error" (cadr *error*)))
               );or 
          );and 
          (setq bonus_old_error *error*);save the *error* only if it 
                                        ;looks like the standard one or is some other 
                                        ;user defined one. Don't want to save it if 
                                        ;it's ours because we already have it.
      );if
      (if (cadr lst)
          (setq bonus_undoctl (undo_init)) 
          (setq bonus_undoctl nil)
      );if
    );progn then this is a top level call, or in other words, the first time through.
 );if
 (b_set_sysvars (car lst))
 (if (= bonus_alive 1)
     (progn
      (setq *error* bonus_error);setq
      (if (caddr lst)
          (setq *error* (append (reverse (cdr (reverse *error*))) 
                                (list (caddr lst)
                                      (last *error*)
                                );list
                        );append
          );setq ;then add additional routine name to the error function.
      );if
     );progn
     (progn
      (if (and (> bonus_alive 1)
               (or (not (equal 'LIST (type *error*)))
                   (not (equal "bonus_error" (cadr *error*)))
               );or
          );and
          (setq *error* bonus_error);setq
      );if
     );progn else double check to make sure the bonus_error is in effect.
 );if
 (if (and ss
          (equal 1 (logand 1 (getvar "pickfirst")))
     );and
     (sssetfirst (car ss) (cadr ss))
 );if
);defun init_bonus_error

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun bonus_error ( msg / )

"bonus_error"

(setq bonus_alive -1)
(print msg)

;;Get out of any active command.
(while (not (equal (getvar "cmdnames") "")) (command nil))

;If undo global variable flag is set then use undo as a cleanup helper.
(if bonus_undoctl
    (progn
     (setvar "cmdecho" 0)

     (while (not (wcmatch (getvar "cmdnames") "*UNDO*"))
            (command "_.undo")
     );while
     (command "_end")  ;The routine that just failed created an undo 
                       ;begin mark, so we need to close it off with 
                       ;and "end" mark.

     (command "_.undo" "1")   ;now back up to the begining.
     (while (not (equal (getvar "cmdnames") "")) 
      (command nil)
     );while

    );progn
);if

(b_restore_sysvars)
(b_restore_undo)

;Restore original error handler
(if bonus_old_error
    (setq *error* bonus_old_error)
);if

(setq bonus_alive 0)

(princ)
);defun bonus_error

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun restore_old_error ( / )

(setq bonus_alive (- bonus_alive 1))
(if (>= bonus_alive 0)
    (b_restore_sysvars)
    (setq bonus_varlist nil)
);if
(if (<= bonus_alive 0)
    (progn
     (b_restore_undo)
     (if bonus_old_error
         (setq *error* bonus_old_error);put the old error routine back.
     );if
    );progn then
);if

(princ)
);defun restore_old_error



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun b_restore_undo ()

(if bonus_undoctl
    (progn
      (b_set_sysvars (list "cmdecho" 0))

      (while (equal 8 (logand 8 (getvar "undoctl")))
         (command "_.undo" "_end")
      );while

      (if (not (equal bonus_undoctl (getvar "undoctl")))
          (progn
           (cond 
            ((equal 0 bonus_undoctl) 
             (command "_.undo" "_control" "_none")
            )
            ((equal 2 (logand 2 bonus_undoctl))
             (command "_.undo" "_control" "_one")
            )	
           );;cond 
           (if (equal 4 (logand 4 bonus_undoctl))
               (command "_.undo" "_auto" "_on") 
           );if 

         );progn then restore undoctl to the status the user had it set to. 
      );if
      (if (not (equal 2 (logand 2 (getvar "undoctl"))))
          (b_restore_sysvars)
      );if
    );progn then restore undo to it's original setting
);if
(setq bonus_undoctl nil)

);defun b_restore_undo


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;This has no error checking. You must
;provide a list of even length in the 
;following form
;( "sysvar1" value
;  "sysvar2" value2
;)
(defun b_set_sysvars (lst / lst2 lst3 a b n)

(setq lst3 (car bonus_varlist));setq

(setq n 0)
(repeat (/ (length lst) 2)
 (setq a (strcase (nth n lst))
       b (nth (+ n 1) lst)
 );setq
 (setq lst2 (append lst2
                    (list (list a (getvar a)))
            );append
 );setq 
 (if (and bonus_varlist 
          (not (assoc a lst3))
     );and
     (setq lst3 (append lst3 
                        (list (list a (getvar a)))
                );append
     );setq 
 );if

 (setvar a b)

(setq n (+ n 2));setq
);repeat
(if bonus_varlist
    (setq bonus_varlist (append (list lst3) 
                                (cdr bonus_varlist)
                                (list lst2) 
                        );append
    );setq
    (setq bonus_varlist (list lst2))
);if
);defun b_set_sysvars

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun b_restore_sysvars ( / lst n a b)

 (if (<= bonus_alive 0)
     (setq           lst (car bonus_varlist)
           bonus_varlist (list lst)
     );setq 
     (setq lst (last bonus_varlist)) 
 );if

 (setq n 0);setq
 (repeat (length lst)
 (setq a (nth n lst)
       b (cadr a)
       a (car a)
 )
 (setvar a b)
 (setq n (+ n 1));setq
 );repeat
 (setq bonus_varlist (reverse (cdr (reverse bonus_varlist))))

);defun b_restore_sysvars

;;;;;;;;;;;;;;;;;;;;;;;;;end error handler functions;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun p_isect ( lst flag2 / flag lst2 lst3 a b c d n j)

(setq n 0);setq
(repeat (length lst)
(setq    a (nth n lst)
      lst2 (append lst2 (list a))
);setq
(if (equal 2 (length lst2))
    (setq lst3 (append lst3 (list lst2))
          lst2 (list (cadr lst2))
    );setq
);if    
(setq n (+ n 1));setq
);repeat

(if (equal 2 (length lst2))
    (setq lst3 (append lst3 (list lst2)));setq
);if    

(setq n 0);setq
(while (and (< n (length lst3))
            (not flag)
       );and
(setq a (nth n lst3)
      b (cadr a)
      a (car a)
);setq
 (setq j (+ n 1))
 (while (and (< j (length lst3)) 
             (not flag)
        );and 
 (setq c (nth j lst3)
       d (cadr c)
       c (car c) 
 );setq
 (if (and (not (equal b c 0.000001))
          (not (equal a d 0.000001))
     );and
     (progn
      (setq flag (inters a b c d))
      (if (and flag 
               flag2
          );and
          (progn
           (princ "\nInvalid. Crossing polygon cannot self intersect.")
           (princ flag2)
          );progn
      );if
     );progn
 );if
 
 (setq j (+ j 1));setq
 );while

(setq n (+ n 1));setq
);while

flag
);defun p_isect

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;zoom_4_select
;Takes - a list of coordinates. If all coords do not lie in
;the current view, zoom_4_select will zoom to the extents 
;of the coords in the list argument.
;Returns - True in the form of two corners points if a zoom operation needs 
;          to be performed and returns nil if not. 
;
(defun zoom_4_select ( lst / a b)

 (setq  lst (lsttrans lst 1 2) 
          a (maxminpnt (lsttrans (viewpnts) 1 2))
          b (maxminpnt (append a lst))
 );setq 

 (if (not (equal a b))
     (progn
      (setq b (list (trans (append (car b) '(0.0))  2 1)
                    (trans (append (cadr b) '(0.0)) 2 1)
              )
      );setq
     );progn
     (setq b nil)
 );if

 b
);defun zoom_4_select


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;maxminpnt
;takes: a list of points
;returns: a list of 2 points the lower left and the upper right
;
;	maxminpnt	 
(defun maxminpnt ( lst / x n a b c d)

(setq x (car lst)
      a (car x)
      b (cadr x)
      c (car x)
      d (cadr x)
      n 1
);setq
(repeat (max (- (length lst) 1) 0)
(setq x (nth n lst));setq
(setq a (min a (car x))
      b (min b (cadr x))
      c (max c (car x))
      d (max d (cadr x))
);setq
(setq n (+ n 1));setq
);repeat
(list (list a b)
      (list c d)
);list
);defun maxminpnt


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;viewpnts
;returns lower left and upper right coords of current view
(defun viewpnts ( / a b c d x)

(setq b (getvar "viewsize")
      c (car (getvar "screensize"))
      d (cadr (getvar "screensize"))
      a (* b (/ c d))
      x (setq x (getvar "viewctr"))
      x (trans x 1 2)
      c (list (- (car x)  (/ a 2.0))
              (- (cadr x) (/ b 2.0))
              0.0
        );list
      d (list (+ (car x)  (/ a 2.0))
              (+ (cadr x) (/ b 2.0))
              0.0
        );list
      c (trans c 2 1)
      d (trans d 2 1) 
);setq

(list c d)
);defun viewpnts


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;pixel_unit
;returns the size of a single pixel in drawing units.
;value depends on current zoom factor.
;
;pixunit/viewsize = one pixel/yscreensize
;
;pixunit=viewsize/yscreensize 
;
(defun pixel_unit ( / x y x1 y1)
 (setq  y (getvar "viewsize")
       x1 (car (getvar "screensize"))
       y1 (cadr (getvar "screensize"))
        x (* y (/ x1 y1))
 );setq
 (max (abs (/ y y1))
      (abs (/ x x1))
 );max
);defun pixel_unit

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;**PLINE** function takes a list and creates a polyline entity
;the list contains a list of coords.
;and optionaly other lists such as (8 . "LAYER")
;				   (40 . WIDTH)
;				   (62 . COLOR)
;	pline	     n a b flag
(defun pline ( lst / n a b flag)


(if (> (length lst) 1)
    (progn
     (if (setq b (assoc 8 lst));setq
	 (setq a (append a (list b)));setq then
     );if
     (if (setq b (assoc 40 lst));setq
	 (setq a (append a (list b)
			    (list (cons 41 (cdr b))
			    );list
		 );append
	 );setq then
     );if
     (if (setq b (assoc 62 lst));setq
	 (setq a (append a (list b)));setq then
     );if

    );progn then
    (setq flag T
	     b (car lst)
    );setq else only a coord list was provided
);if

(setq n 0)
(while (and (not flag)
	    (< n (length lst))
       );and

(if (not (member (nth n lst) a))
    (setq    b (nth n lst)
	  flag T
    );setq then
);if

(setq n (+ n 1));setq
);while

(entmake (append (list '(0 . "POLYLINE")) a));entmake

(setq n 0)
(repeat (length b)

(entmake (list '(0 . "VERTEX")
	       (append (list 10) (nth n b))
	 );list
);entmake

(setq n (+ n 1));setq
);repeat

(entmake '((0 . "SEQEND")));entmake

(princ)
);defun pline

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;**VTLIST** takes a list or a polyline ent name
;RETURNS a list of vertecies in
; WORLD if a list is provided '(na code) and code=0
; CURRENT UCS coords are returned if only na is provided as an argument
;or if a lst is provided and code=1
;
;	
(defun vtlist ( na / dxf e1 lst lst2 code n flag a z)

 ;local function
 (defun dxf (a b / ) (cdr (assoc a b)));defun

(if (equal (type na)
	     (type (list 1))
    );equal
    (setq code (cadr na)
            na (car na)
    );setq then
    (setq code 1);setq else
);if
(setq e1 (entget na));setq
(if (equal 1 (logand 1 (dxf 70 e1)))
    (setq flag 1)
    (setq flag nil)
);if
(if (equal (dxf 0 e1) "POLYLINE")
    (progn
     (setq na (entnext na)
           e1 (entget na)
     );setq
     (while (/= "SEQEND" (dxf 0 e1))    
      (setq lst (append lst 
                        (list (trans (dxf 10 e1) na code));list 
                );append
             na (entnext na)
             e1 (entget na)
      );setq
     );while
    );progn then old polyline
    (progn
     (setq lst e1
             z (dxf 38 e1)
     );setq
     (if (not z) (setq z 0.0)) 
     (setq n 0);setq
     (repeat (length lst)
     (setq    a (nth n lst))
     (if (equal (car a) 10)
         (setq   a (cdr a)
                 a (list (car a) (cadr a) z)
              lst2 (append lst2 
                           (list (trans a na code))
                   );append
         );setq then
     );if
     (setq n (+ n 1));setq 
     );repeat
     (setq  lst lst2 
           lst2 nil
     );setq
    );progn else lwpolyline
);if 
(if (and flag lst)
    (setq lst (append lst (list (car lst))));setq
);if
lst
);defun vtlist

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;ep_list
;returns entity point list
;returns a list of points on the entity
;args
; na -is a polyline 'pl_point_list' is called
; alt -is an arc segmant error tolerance (altitude)
;
(defun ep_list ( na alt / dxf a b c d n e1 lst)

 ;local function
 (defun dxf (a b / ) (cdr (assoc a b)));defun

(setq e1 (entget na));setq
(cond
 ((or (equal (dxf 0 e1) "POLYLINE")
      (equal (dxf 0 e1) "LWPOLYLINE")
  );or
  (setq lst (pl_point_list na alt));setq
 );cond #1
 ((equal (dxf 0 e1) "LINE")
  (setq lst (list (trans (dxf 10 e1) na 1)
                  (trans (dxf 11 e1) na 1)
            );list
  );setq
 );cond #2
 ((or (equal (dxf 0 e1) "ARC") 
      (equal (dxf 0 e1) "CIRCLE")
  );or
  (progn
   (setq a (dxf 10 e1)             ;the center point
         b (dxf 40 e1)             ;the radius
         n (dxf 50 e1)             ;the start angle
         c (dxf 51 e1)             ;the end angle
   );setq
   (if (not n)
       (setq n 0
             c (* 2.0 pi)
       );setq then it's a circle
       (if (> n c)
           (setq c (+ c (* 2.0 pi)));setq then
       );if else it's an arc
   );if
   (setq lst (append lst 
                     (get_arc_points a 
                                     (polar a n b) 
                                     (polar a c b)
                                     (- c n) 
                                     alt
                     );get_arc_points
             );append
   );setq
   (setq lst (lsttrans lst na 1))
  );progn
 );cond #3
;add trim capabilities for text here
; ((equal "TEXT" (dxf 0 e1))
;  (setq p1 (textbox e1)
;
;  );setq
; );cond #4  
);cond close

lst
);defun ep_list

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun pl_point_list ( na alt / dxf na2 a b c z p1 p2 p3 e1 lst lst2 code n flag )

 ;local function
 (defun dxf (a b / ) (cdr (assoc a b)));defun
(load"acadiso")
(princ)
(load"acadiso")
(princ)
(load"acadiso")
(princ)
(load"acadiso")
(princ)
(load"acadiso")
(princ)
