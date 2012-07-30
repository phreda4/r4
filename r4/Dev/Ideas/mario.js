/*
 * The Javascript Mario Experiment v0.1
 * Copyright (c) 2008 Jacob Seidelin, cupboy@gmail.com
 * MIT License [http://www.opensource.org/licenses/mit-license.php]
 */


var Mario = function(bMusic, iScale) {

// our own variables can be compressed, builtin functions can't
var toInt = parseInt,
setTimer = setTimeout,
getElement = function(id){return document.getElementById(id);},
appChild = function(parent, child) {return parent.appendChild(child);},
dc = function(tag) {return document.createElement(tag);},
child = function(e,i){return e.childNodes[i]},
charAt = function(str,idx) {return str.charAt(idx);},
floor = Math.floor, round = Math.round;

// -----------------------------------------------------------------
// begin game setup
// -----------------------------------------------------------------

var bHasCanvas = !!(dc("canvas").getContext);

var bContScroll = bHasCanvas,
iGameTime = 200,
iPlayerWalking = 0,
iPlayerWalkCycle = 0,
iPlayerDirection = 0,
iCurrentPlayerDirection = -1,
iCurrentPlayerState = -1,
iJumpBoost = 0,
iPreJump = 0,
iCoinsCollected = 0,
iPoints = 0,
bIsDead = 0,
iPlayerMovementX = 0,
iPlayerMovementY = 4,
bPlayerIsOnGround = 0,
iScrollX = 0,

oLevelElement,
oPlayerElement,
aTileMap = [],
aMapRows = [],
aSpriteHTML,
aPlayerStates,
aCollisionMap = [];


showHide = function(oElement, bShow) {
	oElement.style.display = bShow ? "block" : "none";
},

// create a string of characters
writeText = function(aChars, x, y, aReplaceChars) {
	var 	aCharSpans = aReplaceChars || [],
		i = 0;
	for (i in aChars) {
		aCharSpans[i] = writeChar(aChars[i], x, y, aCharSpans[i]);
		x += 8 * iPixSize;
	}
	return aCharSpans;
},

// write a single character
writeChar = function(iChar, iCharX, iCharY, oReplaceChar) {

	var 	oCharElement = createSpan(iCharX, iCharY, 7*iPixSize, 7*iPixSize),
		aBits = base128ToBitString(aFont[iChar]),
		i = -1,
		y = 0,
		x = 0;


	var oPixelElement = oCharElement;
	if (bHasCanvas) {
		oPixelElement = child(oCharElement, 0).getContext("2d");
	}

	for (;y < 7; y++) {
		for (x = 1; x < 8; x++) 
			if (aBits[++i]) plotPixel(9, x, y, oPixelElement, 1);
	}
	if (oReplaceChar) oMainElement.removeChild(oReplaceChar);
	return appChild(oMainElement, oCharElement);
},

// create a tile span element
createSpan = function(x, y, w, h, strBGColor, strHTML){
	var 	oElement = dc("span"),
		oStyle = oElement.style;
	if (h) {
		oStyle.width = w;
		oStyle.height = h;
		oStyle.top = y;
		oStyle.left = x;
		oStyle.overflow = "hidden";
	}
	oStyle.position = "absolute";
	oStyle.backgroundColor = strBGColor || "";

	if (bHasCanvas) {
		var oCanvas = dc("canvas");
		oCanvas.style.width = oCanvas.width = w;
		oCanvas.style.height = oCanvas.height = h;
		oCanvas.style.top = oCanvas.style.left = 0;
		oCanvas.style.position = "absolute";
		if (strHTML) {
			oCanvas.getContext("2d").drawImage(strHTML, 0, 0);
		}
		oCanvas.style.backgroundColor = "";
		appChild(oElement, oCanvas);
	} else {
		oElement.innerHTML = strHTML || "";
	}
	return oElement;
},

// update game time text
updateTime = function() {
	if (bIsDead) return;
	var strTimeNow = (--iGameTime)+"";

	while (strTimeNow.length < 3) strTimeNow = 0 + strTimeNow;

	writeText(strTimeNow.split(""), 208*iPixSize, 24*iPixSize, aTimeChars);
	if (iGameTime == 0) iGameTime=200;
	setTimer(updateTime, 1000);
},


// change the player sprite state (walk/jump/etc..)
setPlayerState = function(iNewState) {
	if (bIsDead) return;
	if (iPlayerDirection == iCurrentPlayerDirection && iNewState == iCurrentPlayerState) return ;

	for (var iState in aPlayerStates)
		showHide(aPlayerStates[iState], (iNewState + iPlayerDirection * 4 == iState));

	iCurrentPlayerDirection = iPlayerDirection;
	iCurrentPlayerState = iNewState;
},


// draw tile graphics
drawTile = function(x, y, iHTMLIdx, iHTMLIdx2) {
	var oSpanElement = appChild(oLevelElement, 
		createSpan(x * iTileSize, y * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[iHTMLIdx])
	);
	if (iHTMLIdx2) {
		appChild(oSpanElement, 
			createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[iHTMLIdx2])
		);
	}
	return oSpanElement;
},


// load encoded spritedata to bitstring and generate prototype
loadSpriteData = function(aSpriteColors, strSpriteData, bFlipHori) {

	var aBits = base128ToBitString(strSpriteData);
	if (bHasCanvas) {

		var oSpriteCanvas = dc("canvas");
		var oCanvasCtx = oSpriteCanvas.getContext("2d"); 
		var oStyle = oSpriteCanvas.style;
		oStyle.position = "absolute";
		oStyle.left = oStyle.top = 0;
		oStyle.width = oStyle.height = oSpriteCanvas.width = oSpriteCanvas.height = iTileSize;
	
		if (aPalette[aSpriteColors[0]] != "") {
			oCanvasCtx.fillStyle = "#" + aPalette[aSpriteColors[0]];
			oCanvasCtx.fillRect(0,0,iTileSize,iTileSize);
		}

		loadSpriteBits(aSpriteColors, aBits, oCanvasCtx, bFlipHori);
		return oSpriteCanvas;

	} else {
		var oWrapSpan = createSpan(),
			oSpriteSpan = createSpan(0, 0, iTileSize, iTileSize, aPalette[aSpriteColors[0]]);

		loadSpriteBits(aSpriteColors, aBits, oSpriteSpan, bFlipHori);
		appChild(oWrapSpan, oSpriteSpan);

		return oWrapSpan.innerHTML;
	}

},

// convert base-128 string to bitstring
base128ToBitString = function(strData) {
	var 	aBits = [],
		i = 0,
		b;
	for (; i < strData.length; i++) {
		for (b=6;b>-1;b--)
			aBits.push(CHARMAP[strData.charCodeAt(i)] >> b & 1);
	}
	return aBits;
},

// generate sprite from bitstring
loadSpriteBits = function(aPal, aBits, oSpriteElement, bFlipHori) {
	var 	x = 0, 
		y = 0, 
		iBitCnt = 0, 
		bFirstPixel;

	while (iBitCnt < aBits.length) {
		var 	iColor = (aBits[iBitCnt] << 1) + aBits[++iBitCnt],
			iWidth=0,
			bOne = 0;

		bFirstPixel = 1;
		while (aBits[iBitCnt] == 0 || bFirstPixel) {
			iWidth++;
			iBitCnt++;
			if (++x > 15 || aBits[iBitCnt] == 1){
				var iStartX = x;
				if (bFlipHori) iStartX = iWidth - x + 16;

				plotPixel(aPal[iColor], iStartX, y, oSpriteElement, iWidth);

				if (x > 15) {
					iWidth = x = 0;
					if (++y > 15) return ;
				}
			}
			bFirstPixel = 0;
		}
		iBitCnt++;

		// rewind bitstring if no 1 bits left
		if (aBits.length - iBitCnt < 7) {
		for (var i=iBitCnt;i<aBits.length;i++)
			if (aBits[i] == 1) bOne = 1;
			if (!bOne) {
				if (x) y++;
				x = iBitCnt = 0;
			}
		}
	}
},

// plot a pixel on span element
plotPixel = bHasCanvas ? 
function(iColor, x, y, oCtx, iWidth) {
	if (aPalette[iColor] != "") {
		oCtx.fillStyle = "#" + aPalette[iColor];
		oCtx.fillRect(x * iPixSize - iWidth * iPixSize, y * iPixSize, iWidth * iPixSize, iPixSize);
	}
} : 
function(iColor, x, y, oSpan, iWidth) {
	appChild(oSpan, 
		createSpan(
			(x - iWidth) * iPixSize, 
			y * iPixSize, 
			iWidth * iPixSize, 
			iPixSize,
			aPalette[iColor]
		)
	);
},

// convert bitstring to integer
bitsToInt = function(strBits) {
	var iVal = 0;
	for (var i = 0; i < strBits.length; i++) {
		if (charAt(strBits,i) == "1") {
			iVal = iVal | (1 << ((strBits.length-1) - i));
		}
	}
	return iVal;
},


// animate newly spawned coin
animateCoin = function(oCoinElement, iStep) {
	oCoinElement.style.top = toInt(oCoinElement.style.top) + iStep;
	if (iStep < 8) 
		setTimer(function (){animateCoin(oCoinElement,iStep + 2);}, 30);
	else
		collectCoin(toInt(oCoinElement.style.left), toInt(oCoinElement.style.top));
},


// check for tile collisions and return new adjusted position
getTileCollision = function(iOldX, iOldY, iNewX, iNewY) {

	var oCol, xAdjust=0;

	// moving vertically
	if (iOldY != iNewY) {
		// moving down
		if (iNewY > iOldY) {
			// lower left collision
			oCol = tileCollides(iNewX + iPixSize, iNewY + iTileSize);
			if (oCol && !tileCollides(iNewX + iPixSize, iNewY)) {
				iNewY -= oCol[1];
			}

			// lower right collision
			oCol = tileCollides(iNewX + iTileSize-iPixSize, iNewY + iTileSize);
			if (oCol && !tileCollides(iNewX + iTileSize-iPixSize, iNewY)) {
				iNewY -= oCol[1];
			}
		// moving up
		} else {
			// upper left collision
			oCol = tileCollides(iNewX + iPixSize, iNewY);
			if (oCol && !tileCollides(iNewX + iPixSize, iNewY + iTileSize)) {
				iNewY += (iTileSize - oCol[1]);
			}

			// upper right collision
			oCol = tileCollides(iNewX + iTileSize - iPixSize, iNewY);
			if (oCol && !tileCollides(iNewX + iTileSize - iPixSize, iNewY + iTileSize)) {
				iNewY += (iTileSize - oCol[1]);
				xAdjust = 1;
			}
		}

	}
	// moving horizontally
	if (iOldX != iNewX) {

		// moving right
		if (iNewX > iOldX) {

			// lower right collision
			oCol = tileCollides(iNewX + iTileSize, iNewY + iTileSize-iPixSize);
			if (oCol) {
				iNewX -= oCol[0];
			}

			// upper right collision
			oCol = tileCollides(iNewX + iTileSize, iNewY);
			if (oCol) {
				iNewX -= oCol[0];
			}

		// moving left
		} else {

			// lower left collision
			oCol = tileCollides(iNewX, iNewY + iTileSize-iPixSize);
			if (oCol) {
				iNewX += (iTileSize - oCol[0]);
			}

			// upper left collision
			oCol = tileCollides(iNewX, iNewY);
			if (oCol) {
				iNewX += (iTileSize - oCol[0]);
			}
		}
	}

	return [iNewX,iNewY,xAdjust];
},

// check if a tile is blocking
tileCollides = function(x, y) {
	var tx = floor(x / iTileSize);
	var ty = floor(y / iTileSize);

	if (aCollisionMap[ty] && aCollisionMap[ty][tx]) {
		return [x - tx * iTileSize, y - ty * iTileSize];
	}
},


addPoints = function(iAddPoints) {
	iPoints += iAddPoints;

	var strPoints = ("00000"+iPoints).substr(-5);
	setTimer(
		function() {
			writeText([charAt(strPoints,0),charAt(strPoints,1),charAt(strPoints,2),charAt(strPoints,3),charAt(strPoints,4)], 24*iPixSize, 24*iPixSize, aPointChars);
		}, 1
	);
},


bPlayerMoveX = 0,

fncKeyUp = function (e) {
	var keyCode = (e||event).keyCode;

	if (keyCode == 39 || keyCode == 37)
		bPlayerMoveX = 0;

	if ((keyCode == 17 || keyCode == 38) && !bPlayerIsOnGround && iPlayerMovementY < -4)
		iPlayerMovementY = -4;
},

fncKeyDown = function (e) {
	var keyCode = (e||event).keyCode;
	if (keyCode == 39 && iPlayerMovementX < 1) {
		bPlayerMoveX = 1;
		iPlayerDirection = 0;
	}
	if (keyCode == 37 && iPlayerMovementX > -1) {
		bPlayerMoveX = iPlayerDirection = 1;
	}
	if (keyCode == 17 || keyCode == 38) {
		if (bPlayerIsOnGround)
			jump();
		else
			iPreJump = 8;
	}
},

fncMoveTimer = function() {
	if (bPlayerMoveX) {
		if (iPlayerDirection == 0 && iPlayerMovementX < 6) {
			iPlayerMovementX += 1;
		} else if (iPlayerMovementX > -6) {
			iPlayerMovementX -= 1;
		}
	} else {
		if (iPlayerMovementX < 0)
			iPlayerMovementX++;
		if (iPlayerMovementX > 0)
			iPlayerMovementX--;
	}
	setTimer(fncMoveTimer, 50);
},

jump = function() {
	iPlayerMovementY = -11 - iJumpBoost;
	iJumpBoost = iPreJump = 0;
},

makeSpace = function(n) {
	var str = "";
	while (n>0) {
		str += " "; n--;
	}
	return str;
},


// ----------------------------------------
// data
// ----------------------------------------

iPixSize = iScale || 1,
iTileSize = 16 * iPixSize,
CHARMAP = [];

for (var c = 32, i = 0; c < 256; c++) {
	CHARMAP[c] = i;
	i++;
	if (c == 127) c = 160;
	if (c == 91) c++;

}

var aFont = [
	"<F•••R<", // 0
	",<,,,,`", // 1
	"_•'>]≤¡", // 2
	"`&,>#•_", // 3
	".>V®¡&&", // 4
	"¿¢¿##•_", // 5
	">P¢¿••_", // 6
	"¡•&,888", // 7
	"_••_••_", // 8
	"_••`#&]", // 9
	"•π¡¡≠••",  // M  // yui
	"<V••¡••", // A
	"¿••©æ∞©", // R
	"`,,,,,`", // I
	"_•••••_", // O
	"  B4(4B", // x
	"   ``", // -
	"••≠¡¡π•",  // W  // yui
	"PPPPPP`", // L
	"æ®•••®æ", // D
	"`,,,,,,", // T
	"¡¢¢¿¢¢¡"  // E
	],


//	 	0    1	    2	      3		4	5 	6	 7	  8 	   9	   10	    11	    12
aPalette = ["","FF3900","AD7B00","F7D6B5","000000","E75A10","C0FF2B","00AD00","F0D0B0","FFFFFF","6B8CFF","39BDFF","FFA542"],

aSpriteData = [
	"}\"π-∫\"¿+∫\"¿+∫\"¿+∫\"ø§¿ ~C_ +∫\"¿+∫\"¿+∫\"¿*P7≤OK%æ+Ωu_\"¿<°a°a°bM@±@™",	//  0 ground
	"a ' ![± 7∞≥b£[mt<Nµ7z]~®ORª[f_7l},tl},+}%XN≤Sb[bl£[±%Y_π !@ $",		//  1 qbox
	"!A % @,[] ±}∞@;µn¶&X£ <$ ß§ 8}}@Prc'U#Z'H'@∑ ∂\"is §&08@£(",			//  2 mario
	"  ¥!A.@H#q8∏ªe-ΩnÆ@±oW:&X¢a<&bbX~# }LWP41}k¨#3®q#1f RQ@@:4@$",			//  3 mario jump
	"   40 q$!hWa-Ωn¶#_Y}a©,0#aaPw@=cmY<mq©GBagaq&@q#0ß0t0§ $",			//  4 mario run
	"+hP_@",									//  5 pipe left
	"¢,6< R§",									//  6 pipe right
	"@ &  ,'+hP?>≥Æ'©}[!ªπ.¢_^•y/pX∏#µ∞=aæΩhP?>≥Æ'©}[!ªπ.¢_^  Ba a",		//  7 pipe top left
	"@ , !] \"∫ £] , 8O #7a&+¢ ß≤!c∫ 9] P &O ,4    e",				//  8 pipe top right
	" £ #! ,! P!!vawd/XO§8º'§PΩªπ≤'9®  \"P≤Pa≤(!¢5!N*(4¥b!Gk(a",			//  9 goomba
	"   Xu X5 =ou!Ø≠¨a[Zºq.∞u#|xv ∏∑∑@=~^H'WOJ!Ø≠¨a=Nu ≤J <J   a",			// 10 coin  // yui
	"@ & !MX ~L \"y %P *¢ 5a K  w !L \"y %P *≠a%¨¢ 4  a",				// 11 ebox // yui
	"¢ ,\"≤+aN!@ &7 }\"≤+aN!XH # }\"≤+aN!X%  8}\"≤+aN!X%£@ (",			// 12 bricks
	"} %ø¢!N∞ I®≤*<P%.8\"h,!Cg r• H≥a4X¢*<P%.H#I¨ :a!u !q",			// 13 block
	makeSpace(20) + "4a }@ }0 N( w$ }\" N! +aa",					// 14 bush left
	" r \"≤y!L%aN zPN NyN#≤L}[/cyæ N" + makeSpace(18) + "@",			// 15 bush mid
	makeSpace(18) + "++ !R∑a!x6 &+6 87L ¢6 P+ 8+ (",				// 16 bush right
 	" %©¶ +pq 7> \"≥  s" + makeSpace(25) + "@",					// 17 cloud bottom left
	"a/a_#≤.Q•'•b}8.£®7!X\"K+5cqs%(" + makeSpace(18) + "0",				// 18 cloud bottom mid
	"bP ¢L P+ 8%a,*a%ß@ J" + makeSpace(22) + "(",					// 19 cloud bottom right
	"",			// 20 mushroom
	"",	// koopa 16x24
	"",				// 22 star
	"",							// 23 flagpole
	"",			// 24 flag
	"",					// 25 flagpole top
	"  6  ~  }a }@ }0 }( }$ }\" }! } a} @} 0} (} $} \"≤ $",				// 26 hill slope
	"a } \"m %8 *P!MF 5la\"y %P" + makeSpace(18) + "(",				// 27 hill mid
	makeSpace(30) + "%\" t!DK \"q",							// 28 hill top
	"",			// 29 castle bricks
	"",							// 30 castle doorway bottom
	"",					// 31 castle doorway top
	"",			// 32 castle top
	"",			// 33 castle top 2
	"",				// 34 castle window right
	"",				// 35 castle window left
	"",			// 36 castle flag
	makeSpace(19) + "8@# (9F*RSf.8  A¢$!¢040HD",					// 37 goomba flat
	"     *(!¨#q≥°[_¥Yp~°=<•g=&'PaS≤ø Sbq*<I#*£Ld%Ryd%ºΩe8H8bf#0a",			// 38 mario dead
	"   =  ≥ #b 'N∂ ZΩZ ZΩZ ZΩZ ZΩZ ZΩZ ZΩZ =[q ≤@ ≥  ∂   0",			// 39 coin step 1
	"   ?@ /q /e '§ #≥ !∫a }@ N0 ?( /e '§ #≥  ø  _a  \"",				// 40 coin step 2
	"   /  >  ]  ∫ !≤ #¢ %a +  >  ]  ∫ !≤ #¢ 'a  \"",				// 41 coin step 3
	"   7¢ +≤ *] %> \"p !Ga t¢ I≤ 4∫ *] %> \"p  °  Oa  \""				// 42 coin step 4
],

aPalette1=[0,1,2,12],
aPalette2=[0,4,6,7],
aPalette3=[0,4,9,11],
aPalette4=[0,9,5,12];

aSpriteHTML = ["",
	loadSpriteData([5,4,0,3], aSpriteData[0]),		// 01	Ground
	loadSpriteData([3,4,5,0], aSpriteData[1]),		// 02	Question Box
	loadSpriteData(aPalette2, aSpriteData[5]),		// 03	Pipe Left
	loadSpriteData(aPalette2, aSpriteData[6]),		// 04	Pipe Right
	loadSpriteData(aPalette2, aSpriteData[7]),		// 05	Pipe Top Left
	loadSpriteData(aPalette2, aSpriteData[8]),		// 06	Pipe Top Right
	loadSpriteData([0,3,4,5], aSpriteData[10]),		// 07	Coin
	loadSpriteData([5,4,0,8], aSpriteData[12]),		// 08	Bricks
	loadSpriteData([5,4,0,3], aSpriteData[11]),		// 09	Empty Question Box
	loadSpriteData([4,0,5,8], aSpriteData[13]),		// 10	Block
	loadSpriteData([0,4,5,3], aSpriteData[9]),		// 11	Goomba
	loadSpriteData(aPalette1, aSpriteData[2]),		// 12	Mario
	loadSpriteData(aPalette1, aSpriteData[3]),		// 13	Mario Jump
	loadSpriteData(aPalette1, aSpriteData[4]),		// 14	Mario Run
	loadSpriteData(aPalette1, aSpriteData[2],1),		// 15	Mario (Flipped)
	loadSpriteData(aPalette1, aSpriteData[3],1),		// 16	Mario Jump (Flipped)
	loadSpriteData(aPalette1, aSpriteData[4],1),		// 17	Mario Run (Flipped)
	loadSpriteData([0,4,5,3], aSpriteData[9],1),		// 18	Goomba (Flipped)
	loadSpriteData(aPalette2, aSpriteData[14]),		// 19	Bush Left
	loadSpriteData(aPalette2, aSpriteData[15]),		// 20	Bush Mid
	loadSpriteData(aPalette2, aSpriteData[16]),		// 21	Bush Right
	loadSpriteData(aPalette3, aSpriteData[14]),		// 22	Cloud Left
	loadSpriteData(aPalette3, aSpriteData[15]),		// 23	Cloud Mid
	loadSpriteData(aPalette3, aSpriteData[16]),		// 24	Cloud Right
	loadSpriteData(aPalette3, aSpriteData[17]),		// 25	Cloud Bottom Left
	loadSpriteData(aPalette3, aSpriteData[18]),		// 26	Cloud Bottom Mid
	loadSpriteData(aPalette3, aSpriteData[19]),		// 27	Cloud Bottom Right
	loadSpriteData([0,4,7,0], aSpriteData[26]),		// 28	Hill Slope
	loadSpriteData([0,4,7,0], aSpriteData[26], 1),		// 29	Hill Slope (Flipped)
	loadSpriteData([7,4,7,0], aSpriteData[27]),		// 30	Hill Mid
	loadSpriteData([0,4,7,0], aSpriteData[28]),		// 31	Hill Top
	loadSpriteData([7,4,7,0], ""),				// 32	Hill Mid (Full Color)
	loadSpriteData([12,4,5,0], aSpriteData[1]),		// 33	Question Box (Second Color)
	loadSpriteData(aPalette1, aSpriteData[38]),		// 34	Mario Dead
	loadSpriteData([0,4,5,3], aSpriteData[37]),		// 35	Goomba Flat
	loadSpriteData(aPalette4, aSpriteData[39]),		// 36	Coin anim state 1
	loadSpriteData(aPalette4, aSpriteData[40]),		// 37	Coin anim state 2
	loadSpriteData(aPalette4, aSpriteData[41]),		// 38	Coin anim state 3
	loadSpriteData(aPalette4, aSpriteData[42]),		// 39	Coin anim state 4
];

var strMapPipes = ",™h2}-r@vca",
strMapClouds = "(eRAr&¶B),F§@f2E0u§®3eO2^)∏H0¢•65$U2v*wK0Æ•g0",
strMapBushes = "$Æ5P~fVGzB©;=LπTMv∏y|FØKUØ≠X^§7;~6ª[", // yui
strMapHills = "&Æ|R∑/V~{ºn|g∞=IØ±W_wV¢",
strMapHillsRight = "'Æ•S%/∏£|\"nΩi∞AIø≤Waw_¢",

aMapData = [
	["AQ'f>58v¶|2æ",0,0],							// holes			[66,12,67,12,83,12,84,12,85,12,150,12,151,12]
	[strMapPipes,5,1],							// pipes (top left)		[25,10,35,9,43,8,54,8,160,10,176,10]
	[strMapPipes,6,1,1],							// pipes (top right)		[25,10,35,9,43,8,54,8,160,10,176,10]
	[strMapPipes,3,1,0,1,1],						// pipes (bottom left)		[25,10,35,9,43,8,54,8,160,10,176,10]
	[strMapPipes,4,1,1,1,1],						// pipes (bottom left)		[25,10,35,9,43,8,54,8,160,10,176,10]
	["&¶E1:f2^cNKUMßf6]{k¨lVOß`wp0", 2, 1],					// coin qboxes			[13,9,18,9,19,5,20,9,61,8,75,9,91,5,91,9,98,9,103,9,106,5,106,9,109,9,126,5,127,5,167,9]
	[""],									// mushroom/flower qboxes
	["(¶G1LssmkUIßGv@v*uktJrK%LvTw,}¥∏K~O%_w x∂°µEn:U)", 8, 1],		// bricks			[17,9,19,9,21,9, 74,9, 76,9, 77,5,78,5,79,5,80,5,81,5,82,5,83,5,84,5, 88,5,89,5,90,5, 97,9, 115,9, 118,5,119,5,120,5, 125,5,128,5, 126,9,127,9, 165,9,166,9,168,9]
	[strMapBushes,19,0,-1],							// bushes left
	[strMapBushes,21,0,1],							// bushes right
	[strMapBushes,20,0],							// bushes			[9,11,10,11,11,11,21,11,39,11,40,11,57,11,58,11,59,11,69,11,87,11,88,11,105,11,106,11,107,11,117,11,135,11,136,11,155,11,165,11,203,11]
	[strMapClouds,27,0,1,1],						// cloud bottom right
	[strMapClouds,25,0,-1,1],						// cloud bottom left
	[strMapClouds,22,0,-1],							// cloud top left
	[strMapClouds,24,0,1],							// cloud top right
	[strMapClouds,23,0],							// cloud top			[17,1,25,2,26,2,27,2,34,1,35,1,54,2,65,1,73,2,82,1,83,1,102,2,113,1,121,2,122,2,123,2,130,1,131,1,150,2,161,1,169,2,170,2,171,2,178,1,179,1,198,2]
	[strMapClouds,26,0,0,1],						// cloud bottom
	[strMapHills,31,0,1,-1],						// hills top
	[strMapHills,28,0],							// hills left slope		[13,11,45,11,46,10,61,11,93,11,94,10,109,11,141,11,142,10,157,11,189,11,190,10,205,11]
	[strMapHills,30,0,1],							// hills mid spots (left)
	[strMapHills,32,0,2],							// hills mid blank
	[strMapHillsRight,29,0],						// hills right slope		[15,11,49,11,48,10,63,11,97,11,96,10,111,11,145,11,144,10,159,11,193,11,192,10,207,11]
	[strMapHillsRight,30,0,-1],						// hills mid spots (right)
	["b∞)HL£r)eJQZgNCY5Dµ4ew3(m®UI~ÆxSvsVy|>∞≠c∞IZF.¢",10,1,0,0,1],		// blocks  // yui		[131,11,132,10,133,9,134,8,137,8,138,9,139,10,140,11,145,11,146,10,147,9,148,8,149,8,152,8,153,9,154,10,155,11,178,11,179,10,180,9,181,8,182,7,183,6,184,5,185,4,186,4,195,11]
	[	23,12,-24,1,
		41,12,-4,1,
		52,12,-7,1,
		50,12,-5,3,
		94,12,-8,36,
		92,12,-6,38,
		111,12,-25,19,
		109,12,-23,21,
		121,12,-35,9,
		119,12,-33,11,
		125,12,-39,5,
		123,12,-37,7,
		79,5,-2,5,
		77,5,0,7
	]							// goombas

],


aSounds = [
	// very small, very simple mario theme. Sequenced by Mike Martel.
	"data:audio/mid;base64,TVRoZAAAAAYAAQAEAMBNVHJrAAAAGQD/UQMFe3EA/1gEBAIYCAD/WQIAAAD/LwBNVHJrAAABqwD/AwRCYXNzAP8gAQAAsAdhAMAjhgCQJGGCHoAkQAeQK1qCB5AwXAeAK0CBUZApVQSAMECCJJAwWQmAKUCCD5ApVwGAMECBRJAkXQyAKUCCC5AoWQSAJECCC5ArXA+AKEBGgCtAB5AwU4UjgDBAAZArXIFMgCtAAZAkWYIjkCtYBIAkQIIYkDBXDYArQIEsgDBACZApXIITgClABJAwWYILgDBAA5ApVoFJkCRcAoApQIFPkCxsBIAkQIISgCxABpAubIIEkDBiBIAuQII7kCtiA4AwQDmAK0AgkCtWgUKQJGUQgCtAgQ6AJEAqkCRZgiKQK1gJgCRAgg6AK0AAkDBZgUmAMEADkClOghiQMFEBgClAggiAMEAFkClTgUmQJFwGgClAgiSQKFYLgCRAggiQK1oOgChAT5AwVQOAK0CFFIAwQASQK1aBOJAkXAWAK0CCMJArXASAJECCF4ArQAKQMFeBRpApUwKAMECCHYApQAKQMFaCFoAwQAiQKUGBN5AkWg2AKUCBN5AsbBCAJECCFoAsQAOQLnGCCpAwZAKALkCFEoAwQAD/LwBNVHJrAAACSAD/AwZNZWxvZHkA/yABAQCxB38AwRmHTJFPXyuBT0AskU5mKYFOQDaRTWU3gU1ALpFLdU6BS0BtkUxiaYFMQFeRRFlJgURAEpFFalqBRUALkUhxgUqRRVwIgUhAUZFIbg6BRUBAgUhAB5FKZ3uBSkCBM5FPZDWBT0AhkU5nLYFOQDGRTWUzgU1AKZFLX4EzgUtAE5FMZ36BTEAnkVRugR2BVEAvkVRkRYFUQBmRVGSCfYFUQIFPkU9nMIFPQCqRTmcmgU5AN5FNZjeBTUArkUtlMoFLQIEikUxhQoFMQHiRRFRYkUVhAYFEQFmBRUAJkUhqgUCRRWECgUhAWZFIbAiBRUBDgUhACpFKc4FigUpASJFLdoIFgUtAHZFKc4IEgUpADZFIaYMcgUhAhCuRT2Q4gU9AJJFOZi+BTkAukU1fMoFNQC6RS2qBV4FLQAWRTF6BTpFETx6BTEAxkUVnB4FEQF+RSGANgUVAgSqRRV4IgUhAV5FIYhqBRUAugUhACJFKX4E4gUpAd5FPZS2BT0ArkU5qLIFOQDSRTWBTgU1AEpFLaoFGkUxXBIFLQIEEgUxAMpFUX4ENgVRAKpFUXjqBVEAckVRkgxCBVECBO5FPV1eRTlwWgU9APYFOQBKRTVYugU1ALZFLbIE3kUxUAoFLQIFwkUROCYFMQFSBREAMkUU6U5FIXAGBRUCBLIFIQAmRRVNRgUVACJFIXEyBSEAIkUpBghqBSkALkUtzgguBS0AFkUpnghuBSkAHkUNmhjaBQ0AA/y8ATVRyawAAACwA/wMYU2VxdWVuY2VkIGJ5IE1pa2UgTWFydGVsAP8gAQcAtwdkAMcAAP8vAA",

	"data:,",
	// game over. Sequenced by John N. Engelmann.
	"data:audio/mid;base64,TVRoZAAAAAYAAQADAHhNVHJrAAAAggD/AwlHYW1lIE92ZXIA/wMpZnJvbSBTdXBlciBNYXJpbyBCcm90aGVycyBvbiB0aGUgTmludGVuZG8A/wEHVW5rbndvbgD/ASBTZXF1ZW5jZWQgYnkgSm9obiBOLiBFbmdlbG1hbm4uCgD/WAQDAhgIAP9ZAgAAAP9RAwYagAD/LwBNVHJrAAABAAD/IQEAAP8DB1NxdWFyZXMAwEoAsAduAApAAJBAZABIZDxIAABAADw8ZABDZDxDAAA8ADw3ZABAZFpAAAA3AABBZABFZEVFAAFHZEVHAAFFZEZFAABBAABBZABEZFpEAABGZFpGAABEZFpEAABBAABAZABDZC1DAABAAAA+ZABBZC1BAAA+AABAZABDZIE0sAduDAdtDAdsDAdrDAdqDAdpDAdoDAdnDAdmDAdlDAdkDAdjDAdiDAdhDAdgDAdfDAdeDAddDAdcDAdbDAdaDAdZDAdYDAdXDAdWDAdVDAdUDAdTDAdSDAdRDJBDAABAAACwB1CBcJBBAAFBAAD/LwBNVHJrAAAAywD/IQEAAP8DCFRyaWFuZ2xlAMJKALIHbgAKQACSN2QAK2Q8KwAANwA8NGQAKGQ8KAAANAA8MGQAJGRaJAAAMAAAKWQANWSBUDUAACkAAiVkADFkgg4kZAAwZA8xAAAlAIF/sgduDAdtDAdsDAdrDAdqDAdpDAdoDAdnDAdmDAdlDAdkDAdjDAdiDAdhDAdgDAdfDAdeDAddDAdcDAdbDAdaDAdZDAdYDAdXDAdWDAdVDAdUDAdTDAdSDAdRDJIkAAAwAACyB1AA/y8A"
],

playMusic = function(iSoundID, bLoop) {
	if (!bMusic) return;
	var oEmbed = dc("embed");
	oEmbed.src = aSounds[iSoundID];
	oEmbed.id = "sound_" + iSoundID;
	if (bLoop) oEmbed.setAttribute("loop", "true");
	oEmbed.setAttribute("autostart", "true");
	oEmbed.style.position = "absolute";
	oEmbed.style.left = -1000;
	appChild(document.body, oEmbed);
},


// kill player
die = function() {
	if (bMusic) {
		document.body.removeChild(getElement("sound_0"));
		playMusic(1);
	}
	
	setPlayerState(3);
	bIsDead = 1;
	iPlayerMovementY = -8;

},


// -----------------------------------------------------------------
// init game
// -----------------------------------------------------------------

oMainElement = getElement("game");

oLevelElement = appChild(oMainElement, createSpan(0,0,208*iTileSize,13*iTileSize, aPalette[10]));

oMainElement.style.height = 13 * iTileSize;
oMainElement.style.width = 256*iPixSize;

// write static UI strings
writeText([10,11,12,13,14], 24*iPixSize, 16*iPixSize);
writeText([17,14,12,18,19], 144*iPixSize, 16*iPixSize);
writeText([0,16,0], 152*iPixSize, 24*iPixSize);
writeText([20,13,10,21], 200*iPixSize, 16*iPixSize);

appChild(oMainElement, createSpan(80*iPixSize, 20*iPixSize, iTileSize, iTileSize, "", aSpriteHTML[7]))

// write dynamic UI strings
var aPointChars = writeText([0,0,0,0,0], 24*iPixSize, 24*iPixSize),
aCoinChars = writeText([15,0,0], 96*iPixSize, 24*iPixSize),
aTimeChars = writeText([2,0,0], 208*iPixSize, 24*iPixSize),

aGoombas = [];

// generate level
(function(){
	var i, l, aCurMap;

	for (i = 0; i < 13; i++) {
		aMapRows[i] = [];
		aTileMap[i] = [];
		aCollisionMap[i] = [];
	}


	// ground blocks
	for (i = 0; i < 208; i++) {
		aMapRows[12][i] = 1;
		aCollisionMap[12][i] = 1;
	}


	// setup blocks and collision
	for (var m in aMapData) {
		aCurMap = aMapData[m];
		if (aCurMap[0]) {
			var strBits = base128ToBitString(aCurMap[0]).join(""),
			aCoords = [];
			i = 0;
			while (i + 12 <= strBits.length) {
				aCoords.push(bitsToInt(strBits.substring(i, i + 8)));
				aCoords.push(bitsToInt(strBits.substring(i + 8, i + 12)));
				i += 12;
			}
			var iOffX = aCurMap[3] || 0;
			var iOffY = aCurMap[4] || 0;

			for (i = 0; i < aCoords.length; i += 2) {
				var iHeight = 1;
				if (aCurMap[5]) 
					iHeight = 12 - (aCoords[i+1] + iOffY);

				while (--iHeight > -1) {
					var iRow = aCoords[i+1] + iOffY + iHeight,
					iCol = aCoords[i] + iOffX;
					if (aMapRows[iRow]) {
						aMapRows[iRow][iCol] = aCurMap[1];
						aCollisionMap[iRow][iCol] = aCurMap[2];
					}
				}
			}
		
		}
	}


	var aCoinBoxes = [];

	// draw block sprites
	for (i=0;i<13;i++) {
		for (l=0;l<208;l++) {
			if (aMapRows[i][l]) {
				if (aMapRows[i][l] == 2) {
					aTileMap[i][l] = drawTile(
						l, i, 2, 33
					);
					aCoinBoxes.push(aTileMap[i][l]);
				} else {
					aTileMap[i][l] = drawTile(
						l, i, aMapRows[i][l]
					);
				}
				if (l > 32) showHide(aTileMap[i][l]);
			}
		}
	}

	// setup flashing coin boxes timer
	var bCoinBoxFlash = 0;
	var fncFlashCoinBoxes = 
		function() {
			for (var i = 0; i < aCoinBoxes.length; i++) {
				showHide(child(aCoinBoxes[i], 1), bCoinBoxFlash);
			}
			bCoinBoxFlash = !bCoinBoxFlash;
			setTimer(fncFlashCoinBoxes, 100);
		};
	setTimer(fncFlashCoinBoxes, 800);

	// create goombas
	aCurMap = aMapData[24];
	for (i=0; i<aCurMap.length; i+=4) {
		var oGoombaElement = appChild(oLevelElement, 
				createSpan(aCurMap[i] * iTileSize, (aCurMap[i + 1] - 1) * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[11])
		);

		appChild(oGoombaElement, createSpan(aCurMap[i] * iTileSize, (aCurMap[i + 1] - 1) * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[18]).childNodes[0]);
		appChild(oGoombaElement, createSpan(aCurMap[i] * iTileSize, (aCurMap[i + 1] - 1) * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[35]).childNodes[0]);
		showHide(oGoombaElement.childNodes[2]);

		aGoombas.push(oGoombaElement);

		oGoombaElement.m1 = (aCurMap[i + 2] + aCurMap[i]) * iTileSize;
		oGoombaElement.m2 = (aCurMap[i + 3] + aCurMap[i]) * iTileSize;
		oGoombaElement.d = -1;
	}


	// setup goomba walk/flip animation timer
	var bGoombaFlipped = false;
	var fncFlipGoomba = 
		function() {
			for (var i = 0; i < aGoombas.length; i++) {
				if (!aGoombas[i].de) {
					showHide(aGoombas[i].childNodes[0], bGoombaFlipped);
					showHide(aGoombas[i].childNodes[1], !bGoombaFlipped);
				}
			}
			bGoombaFlipped=!bGoombaFlipped;
			setTimer(fncFlipGoomba, 300);
		};
	setTimer(fncFlipGoomba, 300);

	// setup coin animation timer
	var iCoinState = 0;
	var fncAnimCoin = 
		function() {
			for (var i = 0; i < aCoinSprites.length; i++) {
				if (aCoinSprites[i]) {
					showHide(aCoinSprites[i].s[0]);
					showHide(aCoinSprites[i].s[1]);
					showHide(aCoinSprites[i].s[2]);
					showHide(aCoinSprites[i].s[3]);
				}
				showHide(aCoinSprites[i].s[iCoinState],1);
			}
			iCoinState++;
			if (iCoinState == 4) iCoinState = 0;
			setTimer(fncAnimCoin, 100);
		};
	setTimer(fncAnimCoin, 500);
	

})();
// end level generation


// setup player sprite
oPlayerElement = appChild(oLevelElement, createSpan(4*iTileSize,4*iTileSize,iTileSize,iTileSize)),
aPlayerStates = [
	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[12])), // stand right
	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[13])), // walk right
	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[14])), // jump right
	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[34])), // dead

	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[15])), // stand left
	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[16])), // walk left
	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[17])), // jump left
	appChild(oPlayerElement, createSpan(0, 0, iTileSize, iTileSize, "", aSpriteHTML[34]))  // dead
];

setPlayerState(0);

var aCoinSprites = [],

gameCycle = function() {
	var	oPlayerStyle = oPlayerElement.style,
		iCurX = toInt(oPlayerStyle.left),
		iCurY = toInt(oPlayerStyle.top),
		iNewX = toInt(oPlayerStyle.left) + (iPlayerMovementX * iPixSize),
		iNewY = toInt(oPlayerStyle.top) + (iPlayerMovementY * iPixSize),
		oCollideTile,
		i,
		iNewTileY = floor(iNewY / iTileSize),
		iNewState,
		iMoveX = iPlayerMovementX;


	if (iNewTileY > 0 && !bIsDead) {

		bPlayerIsOnGround = 0;

		oCollideTile = getTileCollision(iCurX, iCurY, iNewX, iNewY);

		// collision
		if (oCollideTile) {

			// player could not move lower, must be on ground now
			if (oCollideTile[1] < iNewY) {
				bPlayerIsOnGround = 1;
				iPreJump = 0;
			}

			// player could not move higher, must be falling now
			if (oCollideTile[1] > iNewY) {
				iPlayerMovementY = 1;

				var cx = floor(oCollideTile[0] / iTileSize + 0.5);

				var iBlockY = oCollideTile[1] / iTileSize - 1;

				// check if we hit a coin box
				if (aMapRows[iBlockY][cx] == 2) {

					aMapRows[iBlockY][cx] = 9;

					oLevelElement.removeChild(aTileMap[iBlockY][cx]);

					aTileMap[iBlockY][cx] = appChild(oLevelElement, 
						createSpan(cx * iTileSize, iBlockY * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[9])
					);
					aTileMap[iBlockY][cx].style.top = (iBlockY * iTileSize) - iPixSize * 4;
					setTimer(function() {aTileMap[iBlockY][cx].style.top = (iBlockY * iTileSize) - iPixSize * 2}, 50);
					setTimer(function() {aTileMap[iBlockY][cx].style.top = (iBlockY * iTileSize) - iPixSize}, 100);
					setTimer(function() {aTileMap[iBlockY][cx].style.top = (iBlockY * iTileSize)}, 150);

					// spawn coin
					aMapRows[iBlockY-1][cx] = -1;
					var oCoin = aTileMap[iBlockY-1][cx] = drawTile(cx, iBlockY-1, 36);
					oCoin.s = [
						child(oCoin,0),				// front face
						appChild(oCoin, child(createSpan(cx * iTileSize, (iBlockY-1) * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[37]),0)),
						appChild(oCoin, child(createSpan(cx * iTileSize, (iBlockY-1) * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[38]),0)), // sideways
						appChild(oCoin, child(createSpan(cx * iTileSize, (iBlockY-1) * iTileSize, iTileSize, iTileSize, "", aSpriteHTML[39]),0))
					];

					showHide(oCoin.s[0],1);
					showHide(oCoin.s[1]);
					showHide(oCoin.s[2]);
					showHide(oCoin.s[3]);

					aCoinSprites.push(oCoin);
					animateCoin(oCoin,-8);
				}

			}

			// set new position to collision adjusted coords
			iNewX = oCollideTile[0];
			iNewY = oCollideTile[1];

		}

		iNewX = toInt(iNewX);
		iNewY = toInt(iNewY);

		if (iNewY >= (12 * iTileSize)) {
			die();
		}


		if (bPlayerIsOnGround) {
			iPlayerMovementY = 1;
			if (iMoveX != 0) {
				if (iPlayerWalking == 0) {
					iPlayerWalkCycle = 1;
					iNewState = 0;
				} else if (iPlayerWalking == 2){
					iPlayerWalkCycle = -1;
					iNewState = 2;
				}
				iPlayerWalking+=iPlayerWalkCycle;
			} else iNewState = 0;
		} else {
			iNewState = 1;
		}


		// coin collect
		if (aMapRows[round(iNewY / iTileSize)][floor(iNewX / iTileSize + 0.5)] == -1) {
			collectCoin(iNewX, iNewY);
		}

	}

	// constantly increase fall speed to the max
	if (iPlayerMovementY < 8) iPlayerMovementY++;


	// even dead marios fall
	oPlayerStyle.top = iNewY;

	
	if (!bIsDead) {
		oPlayerStyle.left = iNewX;

		if (oPlayerElement.offsetLeft+oLevelElement.offsetLeft > (bContScroll ? 132*iPixSize : 192*iPixSize)) iScrollX = bContScroll ? -4*iPixSize : -80*iPixSize;
		if (oPlayerElement.offsetLeft+oLevelElement.offsetLeft < (bContScroll ? 124*iPixSize : 48*iPixSize)) iScrollX = bContScroll ? 4*iPixSize : 96*iPixSize;



		// move goombas and check for goomba collision
		var bKilledGoomba = 0;
		for (i in aGoombas) {
			var 	oGoomba = aGoombas[i],
				iGoombaX = toInt(oGoomba.style.left) + oGoomba.d * iPixSize;

			if (!oGoomba.de) {
				oGoomba.style.left = iGoombaX;
				if (iGoombaX < oGoomba.m1) oGoomba.d = 1;
				if (iGoombaX > oGoomba.m2) oGoomba.d = -1;
		
				var iHitX = ((iGoombaX / iTileSize) - (iNewX + iPixSize*8) / iTileSize)
				var iHitY = ((toInt(oGoomba.style.top) / iTileSize) - (iNewY + iPixSize*8) / iTileSize)
	
				// player has x collision with goomba
				if (iHitX <= 0.5 && iHitX >= -1.5) {
					// player has y collision with goomba
					if (iHitY <= 0.5 && iHitY >= -1.5) {
	
						// player above goomba and moving down, kill goomba
						if (iPlayerMovementY > 0 && toInt(oGoomba.style.top) > iNewY) {
							oGoomba.de = 1;
							oGoomba.style.top = toInt(oGoomba.style.top) + iPixSize * 2;

							showHide(oGoomba.childNodes[0]);
							showHide(oGoomba.childNodes[1]);
							showHide(oGoomba.childNodes[2], 1);

							bKilledGoomba = true;
							addPoints(100);
						} else {
							// close x contact
							if (iHitX <= 0.5 && iHitX >= -1.5) {
								// kill player
								die();
							}
						}
					}
				}
			}
		}
		if (bKilledGoomba) {
			iJumpBoost = 1;
			if (iPreJump > 0) {
				jump();
			} else {
				iPlayerMovementY = -3;
			}
		}

		if (iNewState>-1) setPlayerState(iNewState);
	}
	iPreJump--;

	setTimer(gameCycle, 32);
},

collectCoin = function(iX, iY)
{
	iCoinsCollected++;
	aTileMap[round(iY / iTileSize)][floor(iX / iTileSize + 0.5)].innerHTML = "";
	aMapRows[round(iY / iTileSize)][floor(iX / iTileSize + 0.5)] = 0;

	var strCoins = iCoinsCollected+"";
	if (strCoins.length < 2) strCoins = 0 + strCoins;

	writeText([15,charAt(strCoins,0),charAt(strCoins,1)], 96*iPixSize, 24*iPixSize, aCoinChars);
	addPoints(100);
},

checkScroll = function() {
	if (iScrollX != 0) {
		var x;

		if (bContScroll) {
			if (iScrollX > 0)
				x = 4*iPixSize;
			else 
				x = -4*iPixSize;
		} else {
			if (iScrollX > 0)
				x = 8*iPixSize;
			else 
				x = -8*iPixSize;
		}	

		var iNewX = toInt(oLevelElement.style.left) + x;

		if (iNewX < 0) {
			oLevelElement.style.left = iNewX;
			var 	iLeftX = floor(-iNewX / iTileSize)-1,
				iRightX = iLeftX + 17,
				bShowRight;
			if (x > 0) {
				iRightX++;
				iLeftX++;
				bShowRight = 1;
			}
			for (var iRow in aTileMap) {
				var aRow = aTileMap[iRow];
				if (aRow[iRightX]) showHide(aRow[iRightX], !bShowRight);
				if (aRow[iLeftX]) showHide(aRow[iLeftX], bShowRight);
			}
		}
		iScrollX -= x;
	}
	setTimer(checkScroll, 32);
}


// start game

setTimer(gameCycle, 5);
setTimer(updateTime, 1000);
setTimer(checkScroll, 50);
setTimer(fncMoveTimer, 50);

playMusic(0, true);

// we have to move focus from the embedded music to the game container
setTimer(
	function() {
		oMainElement.focus();
	}, 100
);
document.onkeyup = fncKeyUp;
document.onkeydown = fncKeyDown;

}
