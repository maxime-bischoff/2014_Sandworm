

os.chdir(SCRIPT_FILENAME)
Display.mode(480,272)
Input.enableHandlers(false)

merge("Resources/vernando.pak")
--merge("Maps/menu.pak")
merge("Resources/PlayerMesh.pak")
merge("Resources/column.pak")

merge("Resources/area.pak")
merge("Resources/offering.pak")

--merge("Resources/Text/FontArial42.pak")
merge("Resources/Text/FontTacoSalad83.pak")
merge("Resources/Text/FontBurrito90.pak")
merge("Resources/hud.pak")









local myFont = Font.first()	

myFont:digitWidth(0.04)	
columnMesh =  Transform.find("Column")
columnMesh:position(Vector(1000,groundHeight,1000))


Shader.find("areaShader"):setPriority(9)


mainMenu = {}
levelSelectMenu = {}
gameOverMenu = {}
winMenu = {}
pauseMenu = {}

groundHeight = -5

destDevice = "PC"


scaleSandShaderPass1 = 8
scaleSandShaderPass2 = 2
scaleSandShaderPass3 = 3
textOffset = 0


------------------------------------------------
------------ PLAYER ----------------------------





player = SkinMesh.find("polySurface11")
playerTransform = Transform.new("playerTransform")
player:parent(playerTransform)
--player:shader():matDiffuse(Vector( 0.7 , 0.5, 0.4 ) )
--player:shader():matDiffuse(Vector( 0.7 , 0.5, 0.4 ) )

rocketTransform =  Transform.find("rocket")


blockList = {}
tOfferingList = {}
offeringCount = 0
offeringStarterId = 0

areaList = {}
areaCount = 0

areaLogoList = {}
areaLogoCount = 0

tWallList={}
wallCount = 0

columnList = {}
columnCount = 0

rewardList = {}
rewardList = 0;


------------------------------------------------
------------ SANDWORM --------------------------


tailList = {}
tailCount =0

wormRoot = Joint.find("rootJoint")
wormHead = Joint.find("headJoint")
tailList[1] = Joint.find("tail1Joint")
tailList[2] = Joint.find("tail2Joint")
tailList[3] = Joint.find("tail3Joint")
tailList[4] = Joint.find("tail4Joint")


KUP = 20
KDOWN  = 21
KLEFT = 22
KRIGHT = 23


Input.setCtrlMapping(KLEFT, 			TARGET=="PC"  and "KB_A")
Input.setCtrlMapping(KDOWN,				TARGET=="PC"  and "KB_S")
Input.setCtrlMapping(KRIGHT, 			TARGET=="PC"  and "KB_D")
Input.setCtrlMapping(KUP, 				TARGET=="PC"  and "KB_W" )


------------------------------------------------
----------------- HUD --------------------------






warningLogo =  Transform.find("warningLogo")

rotateArrowAxis =  Transform.find("rotateArrowAxis")
areaLogo = Transform.find("areaLogo")
gameOverPlane = Mesh.find("gameOverPlane")
menuPlane = Mesh.find("menuBackGroundPlane")
menuPlane:visible(false)

succeedPlane = Mesh.find("succeedPlane")
pausePlane = Mesh.find("pausePlane")
titleTransform = Transform.find("titleTransform")
titleTransformAxis = Transform.find("titleRotationAxis")


fadePlane =  Mesh.find("fadePlane")

fadePlane:shader():setPriority(10)








offeringRoot = Transform.find("offeringRoot")
offeringRoot:position(Vector(1000,0,1000))
areaRoot = Transform.find("areaRoot")
areaRoot:position(Vector(1000,0,1000))


function FadePlane(iValue)

	fadePlane:shader():matOpacity(iValue)

end




---------------------------------------------------------------------------
-- Camera Parameters 
---------------------------------------------------------------------------

camera =  Camera.getActive()




cameraBobValue = 0

CameraMenuFov = 70													
camera:fov(CameraMenuFov)
cameraTargetPosition =  Vector(0,0,0)
cameraTargetRotation =  Vector(0,0,0)
cameraTargetLookatOffset =  Vector(0,0,0)


cameraCurrentLookatOffset =  Vector(0,0,0)

cameraLocalPosition = Vector(0,0,0)

cameraRunPosition = Vector(0,25,3)
cameraRunRotation = Vector(0,-90,0)
cameraLookatOffsetRun = Vector( 0,0,0)

											cameraRunPosition = Vector(0,65,10)
											cameraRunRotation = Vector(0,-90,0)
											cameraLookatOffsetRun = Vector( 0,0,0)
											cameraRunFov = 30


cameraWalkPosition = Vector(0,4,4)
cameraWalkRotation = Vector(0,-45,0)
cameraLookatOffsetWalk = Vector( 0,2,0)
cameraWalkFov = 70



cameraTargetPosition = cameraWalkPosition
cameraTargetRotation = cameraWalkRotation
cameraTargetLookatOffset =  cameraLookatOffsetWalk
cameraTargetFov = cameraWalkFov

cameraMode = "Walk"

camera:backColor(Vector(0.4,0.5,0.8,1))





-------------------------------------------------- 
------------------- LIGHTS -----------------------
----------------------------------------------------







------------------ create some lights
light1 = Light.new("light1")
light1:setAttr {	mDiffuseColor=Vector(1,0,0),	 mAmbientColor=Vector(0,0,0),  	mSpecularColor=Vector(1,1,1), mType=0 , mSpecular=1}	-- type  0=directional    1=point light
light1:rotation(0,90,0)

light2 = Light.new("light2")
light2:setAttr {	mDiffuseColor=Vector(0,1,0), 	mAmbientColor=Vector(0,0,0), 	mType=0 }	-- type  0=directional    1=point light
light2:rotation(0,-90,0)

light3 = Light.new("light3")
light3:setAttr {	mDiffuseColor=Vector(0,0,1), 	mAmbientColor=Vector(0,0,0),	mType=0}	-- type  0=directional    1=point light
light3:rotation(90,0,0)

light4 = Light.new("light4")
light4:setAttr {	mDiffuseColor=Vector(.5,.5,0), 	mAmbientColor=Vector(0,0,0),	mType=0}	-- type  0=directional    1=point light			
light4:rotation(-90,0,0)

light5 = Light.new("light5")
light5:setAttr {	mDiffuseColor=Vector(1,1,0), 	mAmbientColor=Vector(0,0,0),	mType=1}	-- type  0=directional    1=point light			
light5:rotation(0,0,0)
light5:radius(15)

--------------------------- create a lightset with 4 lights and use it as default
lightSet1 = LightSet.new("fourLights")
lightSet1.mLights[1] = light1
lightSet1.mLights[2] = light2
lightSet1.mLights[3] = light3
lightSet1.mLights[4] = light4
lightSet1.mPower=20


 --create lights 
directLight = Light.new("directLight")
directLight:setAttr {mDiffuseColor=Vector(1,.9,.7),mAmbientColor=Vector(0,0,0), mType=0 }
directLight:rotation(45, 0, 0)







--------------------------------------------------------------
---------------- TEXTS AND FONTS -----------------------------
--------------------------------------------------------------


 local selectedMenuStyle = 
{
	font = "FontTacoSalad83",							-- use string to define the font
--	scale=Vector(8,8),					-- scale vector
	color = "white",							-- use string to define the color (run the cmd Mesh.createText() to retrieve the list of predifined font color)
	alignx="center",							-- use string to define alignement id 0
	charStyle = "normal",				-- use string to define style id 1
	charOffset=Vector(.006,-.006)	-- shadow offset x/y
}


 local unselectedMenuStyle = 
{
	font = "FontTacoSalad83",				-- use string to define the font
	--scale=Vector(5,5),					-- scale vector
	color = "white",						-- use string to define the color (run the cmd Mesh.createText() to retrieve the list of predifined font color)
	alignx="center",						-- use string to define alignement id 0
	charStyle = "normal",					-- use string to define style id 1
	charOffset=Vector(.006,-.006)			-- shadow offset x/y
}

 local numberStyle = 
{
	font = "FontBurrito90",				-- use string to define the font
	--scale=Vector(5,5),					-- scale vector
	color = "white",						-- use string to define the color (run the cmd Mesh.createText() to retrieve the list of predifined font color)
	alignx="center",						-- use string to define alignement id 0
	charStyle = "normal",					-- use string to define style id 1
	charOffset=Vector(.006,-.006)			-- shadow offset x/y
}


scorePosition = Transform.find("scorePosition")
eggCount = Mesh.createText{ str="0", style=numberStyle, pos=Vector(0  ,0 ,0), overlay=true }
eggSlash = Mesh.createText{ str="/", style=numberStyle, pos=Vector(0.1,-0.05 ,0), overlay=true }
eggTotal = Mesh.createText{ str="0", style=numberStyle, pos=Vector(0.2,-0.1 ,0), overlay=true }
eggCount:visible(false)
eggSlash:visible(false)
eggTotal:visible(false)


offeringMesh = Mesh.find("offeringMesh")
offeringHud = offeringMesh:clone("offeringClone")


offeringHud:overlay(true)

offeringHud:position(Vector(0,0,0))
offeringHud:scale(Vector(0.2,0.2,0.2))
--offeringHud:shader():matEmissive(Vector(0.5,0.5,0.5))
offeringHud:shader():setPriority(7)
offeringHud:visible(false)
offeringHud:parent(scorePosition)
offeringHud:position(Vector(0.25,-0.05,0))


eggCount:parent(scorePosition)
eggSlash:parent(scorePosition)
eggTotal:parent(scorePosition)


function UnselectButton( text  )


text:shader():matEmissive(  Vector(0,0,0,1 )  )
text:scale(Vector(1.2,1.2))


end


function SelectButton( text  )

text:shader():matEmissive(Vector(0.3,0.2,0,1 )  )
text:scale(Vector(1.3,1.3))

end








--------------------------------------------------------------------------------------------
-- PARTICLES
-------------------------------------------------------------------------------------------

sandTrail = ParticleSystem.new{ mAutoStart=true }
rocketTrail = ParticleSystem.new{ mAutoStart=true }
 sandTrailPlaying = false
 rocketTrailPlaying = false


texture1 = Texture.new()
texture1:loadFile("Resources/1_2.tga")
texture2 = Texture.new()
texture2:loadFile("Resources/FxSmoke.tga")
texture3 = Texture.new()
texture3:loadFile("Resources/TexWhiteCloud_A.tga")
texture4 = Texture.new()
texture4:loadFile("Resources/TexGlow_A.tga")

sandTrailShader = Shader.new()
sandTrailShader:texture(0,texture4)
sandTrailShader:blendMode("ADD")
sandTrailShader:setPriority(10)
sandTrailShader:flags{ nozwrite=1,unlit=1}

rocketTrailShader = Shader.new()
rocketTrailShader:texture(0,texture4)
rocketTrailShader:blendMode("ADD")
rocketTrailShader:setPriority(10)
rocketTrailShader:flags{ nozwrite=1,unlit=1}


rocketTrail:parent(rocketTransform)







rocketTrail.mEmitterArray[1] =
{

	mShader = rocketTrailShader,
	mParticleNb =		40,
	mPath =				{}, 
	mCpuFade =	1,

	mVolume = Vector( 0.1, 0, 0 ),
	--	mDirection = Vector(0,0,-10),
	mLifeArray=
	{
		{
		--	mLifeDuration =	Vector( 1, 1 ),
          mLifeDuration =				Vector( 0.04, 0.2 ),
			

			mRebirth =		1,
			mResetPos =		1,
			mDirection = Vector(0,0,0),
			mStartingVelocityInTangentSpace = false,
			mStartingVelocityMin =		Vector( 0, 0, -5 ),
			mStartingVelocityMax =		Vector( 0, 0, -5 ),

	
			
			-- mAngularVelocity =			Vector( 0, 0, 0, 0 ),
		--	mAngularVelocityDir =	2,


			mScaleMin =					Vector( 1.0, 1.0, 1.0 ),
			mScaleMax =					Vector( 1.0, 1.0, 1.0 ),
			
		--	mForceInTangentSpace = true,
		--	mForceMin =					Vector( 0, 0, -15 ),
		--	mForceMax =					Vector( 0, 0, -15 ),
			
			mRamp =
			{
				{mColor = Vector( 0, 0, 1, 0 )},
				{mColor = Vector( 1, 0, 0, 1 ), mScaleFactor = Vector( 1, 1, 1 ) },
				{mColor = Vector( 1, 1, 0, 0 ), mScaleFactor = Vector( .5, .5, .5 ) },
			}
		}
	}

}


sandTrail.mEmitterArray[1] =
{

	mShader = sandTrailShader,
	mParticleNb =		30,
	mPath =				{}, 
	mCpuFade =	1,

	mVolume = Vector( 0.4, 0, 0 ),
	--	mDirection = Vector(0,0,-10),
	mLifeArray=
	{
		{
		--	mLifeDuration =	Vector( 1, 1 ),
            mLifeDuration =				Vector( 0.3, 1 ),
			

			mRebirth =		1,
			mResetPos =		1,
		--	mDirection = Vector(0,0,0),

			--mStartingVelocityInTangentSpace = false,

			mStartingVelocityMin =		Vector( 0, 0, -5 ),
			mStartingVelocityMax =		Vector( 0, 0, -5 ),

	
			
			--mAngularVelocity =			Vector( 0, 0, 0, 0 ),
			--mAngularVelocityDir =	2,


			mScaleMin =					Vector( 1.0, 1.0, 1.0 ),
			mScaleMax =					Vector( 1.0, 1.0, 1.0 ),
			
		--	mForceInTangentSpace = true,
		--	mForceMin =					Vector( 0, 0, -15 ),
		--	mForceMax =					Vector( 0, 0, -15 ),
			
			mRamp =
			{
				{mColor = Vector( 0.1, 0.1, 0.1, 1 ), mScaleFactor = Vector( .5, .5, .5 ) },
				{mColor = Vector( 0.3, 0.3, 0.1, 1 ), mScaleFactor = Vector( 1, 1, 1 ) },
				{mColor = Vector( 0.5, 0.5, 0.1, 0 ), mScaleFactor = Vector( .5, .5, .5 ) },
			}
		}
	}

}




--ps2.mEmitterArray[1].mShader:texture( 0, texture2 )

--ps2.mEmitterArray[1].mShader:priority( 10 )





function EnableRocketTrail(bool)


	if(bool == false) then
		if rocketTrailPlaying == true then	
				rocketTrail:stop() 
				rocketTrailPlaying = false
			end
			
	else if rocketTrailPlaying == false then	
				rocketTrail:play() 
				rocketTrailPlaying = true
			end
		
		end



end


function EnableSandTrail(bool)


	if(bool == false) then
		if sandTrailPlaying == true then	
				sandTrail:stop() 
				sandTrailPlaying = false
			end
			
	else if sandTrailPlaying == false then	
				sandTrail:play() 
				sandTrailPlaying = true
			end
		
		end


end





---------------------------------------------------------------------------------------------------------------
--  ----------------------------------------- Blender animation -----------------------------------------------
---------------------------------------------------------------------------------------------------------------

playerBlender = AnimBlender.new( "PlayerBlender" )
playerBlender:init{ mode = "Space", root = player, ctrlNb = 7 }

--idleAnimData:speed( 100 ); -- 100 times faster
idleAnimData = AnimData.find( "Idle" )
sneakAnimData = AnimData.find( "Sneak" )
walkAnimData = AnimData.find( "Walk" )
runAnimData = AnimData.find( "Run" )

jumpAnimData = AnimData.find( "Jump" )

idleHoverAnimData = AnimData.find( "IdleHover" )
runHoverAnimData = AnimData.find( "RunHover" )




idleBlenderAnimData 	= playerBlender:play( idleAnimData );
sneakBlenderAnimData 	= playerBlender:play( sneakAnimData );
walkBlenderAnimData 	= playerBlender:play( walkAnimData );
runBlenderAnimData 		= playerBlender:play( runAnimData );

jumpBlenderAnimData 	= playerBlender:play( jumpAnimData );

idleHoverBlenderAnimData 	= playerBlender:play( idleHoverAnimData );
runHoverBlenderAnimData		= playerBlender:play( runHoverAnimData );



-- initialize cyclism
playerBlender:cyclic( idleBlenderAnimData, true )
playerBlender:cyclic( sneakBlenderAnimData, true )
playerBlender:cyclic( walkBlenderAnimData, true )
playerBlender:cyclic( runBlenderAnimData, true )

playerBlender:cyclic( jumpBlenderAnimData, true )

playerBlender:cyclic( idleHoverBlenderAnimData, true )
playerBlender:cyclic( runHoverBlenderAnimData, true )


-- create position for animation
idlePosition	= Vector( 0,   0,  0,   0.5);
sneakPosition 	= Vector( 0.5, 0,  0,   0.5);
walkPosition 	= Vector( 1,   0,  0,   0.5);
runPosition 	= Vector( 1.75, 0,  0,   0.5);
jumpPosition 	= Vector( 0.75,   1,  0,   1);

idleHoverPosition 	= Vector( 1,   -2,  0,   0.5);
runHoverPosition 	= Vector( 1.75, -2,  0,   0.75);


currentPosition = idlePosition;

-- unite position with animation
playerBlender:spaceAnim( idleBlenderAnimData, idlePosition);
playerBlender:spaceAnim( sneakBlenderAnimData, sneakPosition);
playerBlender:spaceAnim( walkBlenderAnimData, walkPosition);
playerBlender:spaceAnim( runBlenderAnimData, runPosition);

playerBlender:spaceAnim( jumpBlenderAnimData, jumpPosition);

playerBlender:spaceAnim( idleHoverBlenderAnimData, idleHoverPosition);
playerBlender:spaceAnim( runHoverBlenderAnimData, runHoverPosition);



-- synchronize both
playerBlender:synchronize( sneakBlenderAnimData, true )
playerBlender:synchronize( walkBlenderAnimData, true )
playerBlender:synchronize( runBlenderAnimData, true )





function Land()


end



function BlendAnimWalking(speed, walkSpeed, runSpeed, maxSpeed, height)

	transitionDuration = 0.15


	local scaledLerpValue = Clock.deltaTime()/transitionDuration;
	--print ("Height = ")
--[[
	if height > 0.1 then
				currentPosition = currentPosition:lerp( jumpPosition, scaledLerpValue )
			--	print("jump")
	elseif speed < 0.1  then
				currentPosition = currentPosition:lerp( idlePosition, scaledLerpValue )
			--	print("idle")
	elseif speed <walkSpeed then
				currentPosition = currentPosition:lerp( walkPosition, scaledLerpValue )
			--	print("walk")
	else
				currentPosition = currentPosition:lerp( runPosition, scaledLerpValue )
		--	print("run")
	end
	
	]]

	

	if height > 0.05 then
		
				currentPosition = currentPosition:lerp( jumpPosition, scaledLerpValue )
		
	else

				currentPosition = currentPosition:lerp( Vector( 1.75 * (speed /maxSpeed),0,0,0.5)   , scaledLerpValue )	
	
	end
	



	playerBlender:spacePos( currentPosition )
		

end


function BlendAnimHovering(speed,  maxSpeed)
	local transitionDuration = 0.15

	local scaledLerpValue = Clock.deltaTime()/transitionDuration;

	currentPosition = currentPosition:lerp( Vector( 1 + 0.75 * (speed /maxSpeed),-2,0,0.5)   , scaledLerpValue )		

	playerBlender:spacePos( currentPosition )
		

end








function CreateWall(posX, posY, sizeX, sizeY, angle)


	wallCount = wallCount+1
	tWallList[wallCount] =  Mesh.createBox( sizeX, 3, sizeY )
	
	tWallList[wallCount]:position(Vector(posX, 0, posY))

end


function SetEggTotal(value)
	eggTotal:text(value)
	
end

function SetEggCount(value)
	eggCount:text(value)
end

function DisplayEgg(bool)

	eggCount:visible(bool)
	eggTotal:visible(bool)
	eggSlash:visible(bool)
	offeringHud:visible(bool)
end


function CreateArea(maxArea)


	for i = 1, maxArea do

	
		areaList[i] = areaRoot:clone("areaClone")	
		areaList[i]:visible(false)
		areaCount = areaCount+1
	

		areaLogoList[i] = areaLogo:clone("areaLogoClone")	

		--areaLogoList[i]:position(Vector(0,0))
		areaLogoList[i]:visible(false)
		arealogoCount = areaLogoCount+1





	end 

end

function PlaceArea(posX, posY, id)

	areaList[id]:position(Vector( posX, groundHeight, posY))	
	areaList[id]:visible(false)


	areaLogoList[id]:visible(true)


	local areaScreenPos =  camera:worldToScreen(areaList[id]:position() )
	local posX =  areaScreenPos.x  * screenRatio
	local posY =  areaScreenPos.y 
	
	areaLogoList[id]:position(Vector(posX, posY))
	areaLogoList[id]:animPlay("AreaLogoAnim", false)



if destDevice == "PSP" then


		
		found, intersection = layerCollision:intersectRay(columnList[columnCount]:position()+Vector(0,10,0), Vector(0,-1e10,0))

		if found == true then

		
			columnList[columnCount]:position(intersection)
		
		end

	end

end


function PlaceAreaLogo(id)


	local areaScreenPos =  camera:worldToScreen(areaList[id]:position() )
	local posX =  areaScreenPos.x  * screenRatio
	local posY =  areaScreenPos.y 
	
	areaLogoList[id]:position(Vector(posX, posY))



	


end


function SpawnArea(id)

	areaList[id]:animPlay( "SpawnArea", false)
	
	areaList[id]:visible(true)


	areaLogoList[id]:visible( false)
	areaLogoList[id]:animPlay("AreaLogoAnimHide", false)


end

function HideArea(id)

	areaLogoList[id]:visible( false)
	areaList[id]:visible(false)
	areaList[id]:animPlay( "HideArea", false)

end




function CreateOffering(posX, posY, rotation, starter)


offeringRoot:scale(Vector(2,2,2))
	offeringCount = offeringCount +1

	tOfferingList[offeringCount] =  offeringRoot:clone();


	tOfferingList[offeringCount]:position(Vector(posX, groundHeight, posY))

if starter == true then
	tOfferingList[offeringCount]:visible(false)
	offeringStarterId = offeringCount

end


	if destDevice == "PSP" then
		found, intersection = layerCollision:intersectRay(tOfferingList[offeringCount]:worldPivot()+Vector(0,10,0), Vector(0,-1e10,0))
	
		if found == true then
			tOfferingList[offeringCount]:worldPivot(intersection)

		end

	end



end


function PickOffering(id)


	tOfferingList[id]:visible(false)


end

function CreateColumn(posX, posY, rotation)


	columnCount = columnCount+1

	columnList[columnCount] =  columnMesh:clone("Column"..columnCount);


	columnList[columnCount]:position(Vector(posX, groundHeight, posY))

	if destDevice == "PSP" then
		
		found, intersection = layerCollision:intersectRay(columnList[columnCount]:position()+Vector(0,10,0), Vector(0,-1e10,0))

		if found == true then

		
			columnList[columnCount]:position(intersection)
		
		end

	end


end



function ColumnIn(idColumn)
	columnList[idColumn]: animPlay("getIn", false);

	

	screenPos = camera:worldToScreen(columnList[idColumn]:position() ) 
	screenPos.x = screenPos.x* screenRatio


	if  screenPos.x >-1  * screenRatio and screenPos.x <1  * screenRatio and screenPos.y >-1 and screenPos.y <1      then 

		cameraBobValue = 1;

	end


end

function ColumnOut(idColumn)
	columnList[idColumn]: animPlay("getOut", false);
		
end





function SetWalkCamera()

cameraTargetPosition =  cameraWalkPosition
cameraTargetRotation =  cameraWalkRotation
cameraTargetLookatOffset = cameraLookatOffsetWalk
cameraTargetFov = cameraWalkFov
cameraMode = "Walk"
camera:range( 0.5, 10000 )

end

function SetRunCamera()

--camera:range( 10, 200000 )
camera:range( 15,  50000 )

cameraTargetPosition = cameraRunPosition
cameraTargetRotation = cameraRunRotation
cameraTargetLookatOffset = cameraLookatOffsetRun
cameraTargetFov = cameraRunFov
cameraMode = "Run"
end

function ToggleCamera()


	if cameraMode == "Walk" then
		SetRunCamera()

	else 
		SetWalkCamera()
	
	end




end





function UpdateCamera()


	local transitionDuration = 0.15


	local scaledLerpValue = Clock.deltaTime()/transitionDuration

	cameraCurrentLookatOffset = cameraCurrentLookatOffset:lerp(cameraTargetLookatOffset, scaledLerpValue)

	if cameraTargetFov == cameraWalkFov then
	camera:fov(  lerp(camera:fov(), cameraTargetFov, scaledLerpValue/3 ) )

	else 

		camera:fov(  lerp(camera:fov(), cameraTargetFov, scaledLerpValue * 4 ) )
	end

		posX =  math.cos(Clock.time() ) + math.sin(Clock.time())
		posY = math.cos(Clock.time() ) - math.sin(Clock.time())

		cameraBobValue = cameraBobValue - 0.03

	if cameraBobValue <0 then

		cameraBobValue = 0


	end

		cameraLocalPosition = cameraLocalPosition:lerp(cameraTargetPosition, scaledLerpValue)

		camera:position( playerTransform:position() + cameraLocalPosition)

		camera:lookat(playerTransform:position() + cameraCurrentLookatOffset)



	if cameraBobValue >0 then

			local cosA=math.cos(Clock.time()*0.5)  *5    * cameraBobValue
			local cosB=math.cos(Clock.time()*22    ) *3    * cameraBobValue
			local cosC=math.cos(Clock.time()*15   ) *2   * cameraBobValue

			camera:translate( cosA+cosB, 0, cosA-cosC)
			
			
	end



	


end


function Restart()


	for i = 1, columnCount do

	ColumnOut(i)

	end


	for i = 1, areaCount do

		areaList[i]:visible(false)
		areaLogoList[i]:visible(false)
	end

	for i = 1, offeringCount do

		if(i ~= offeringStarterId  ) then
			tOfferingList[i]:visible(true)
		end

	end
	--gameOverPlane:visible(false)
	gameOverPlane:animPlay("GameOverAnimOut", false)
	succeedPlane:animPlay("SucceedAnimOut",false)
	pausePlane:animPlay("PauseAnimOut",false)

	SetWalkCamera()

	playerBlender:spacePos( idlePosition )

EnableRocketTrail(false)
	EnableSandTrail(false)

	menuPlane:visible(false)
	UnFreeze()
	cameraBobValue = 0

end



function UpdateCameraMenu()

	local transitionDuration = 0.90

	local scaledLerpValue = Clock.deltaTime()/transitionDuration

	if(cameraMenuPos2 ~= nil) then

		camera:position( camera:position():lerp( cameraMenuPos2:position(),   scaledLerpValue)  )

		camera:lookat(cameraMenuLookat:position())	


	end



	local cosA=math.cos(Clock.time() *0.3)  
	local cosB=math.cos(Clock.time()  *0.008 )  
	local cosC=math.cos(Clock.time()  *1.5 )   

	titleTransformAxis:rotation( cosA+cosB, 0, cosA-cosC)
			
			
	




end

function LoadMenuMap()

merge("resources/menu.pak")

camera:fov(CameraMenuFov)
cameraMenuPos1 =  Transform.find("cameraPos1")
cameraMenuPos2 =  Transform.find("cameraPos2")
cameraMenuLookat =  Transform.find("cameraTarget")
menu3dEmplacement =  Transform.find("menuShape")

camera:position(cameraMenuPos1:position())
	titleTransform:visible(true)


	sunLight = Light.find("defaultSunLight")
	backLight = Light.find("defaultBackLight")

 sunLight:mDiffuseColor(Vector(1.000000, 1.000000, 1.000000, 0.000000))
 sunLight:mAmbientColor(Vector(0.100000, 0.100000, 0.100000, 0.000000))
 sunLight:rotation(Vector(-29.999998, 0.000000, 0.000000, 0.000000))

 backLight:mDiffuseColor(Vector(0.250000, 0.250000, 0.250000, 0.000000))
 backLight:mAmbientColor(Vector(0.050000, 0.050000, 0.050000, 0.000000))
 backLight:rotation(Vector(149.999985, 0.000000, 0.000000, 0.000000))
 --[[
Vector(1.000000, 1.000000, 1.000000, 0.000000)
Vector(0.100000, 0.100000, 0.100000, 0.000000)
Vector(-29.999998, 0.000000, 0.000000, 0.000000)
Vector(0.250000, 0.250000, 0.250000, 0.000000)
Vector(0.050000, 0.050000, 0.050000, 0.000000)
Vector(149.999985, 0.000000, 0.000000, 0.000000)

]]


menuSandShader = Shader.find("menuSandShader")
	menuSandShader:textureTransform(0,0,0,0,scaleSandShaderPass1,scaleSandShaderPass1)	
	menuSandShader:textureTransform(1,0,3,0,scaleSandShaderPass2,scaleSandShaderPass2)	
DisplayEgg(false)
camera:fov(40)
camera:range(0.1,1500)
end



function UnloadMenuMap()

	menuMap = Transform.find("menuMap")

	if menuMap ~= nil then
		menuMap:release()
	end

end






function ShowMenu(menu, bool)



	if menu == "MainMenu" then 
		for i = 1, #mainMenu do
			mainMenu[i]:visible( bool)
		end

	elseif menu == "PauseMenu" then
		for i = 1, #pauseMenu do

			
			pauseMenu[i]:visible( bool)
		end

	elseif menu == "LevelSelectMenu" then
		for i = 1, #levelSelectMenu do
			levelSelectMenu[i]:visible( bool)
		end
	
	elseif menu == "WinMenu" then
		for i = 1, #winMenu do
			winMenu[i]:visible( bool)
		end

	elseif menu == "GameOverMenu" then
		for i = 1, #gameOverMenu do
			gameOverMenu[i]:visible( bool)
		end

end
	


end

function Pause()


playerBlender:stop(0)
--rocketTrail:stop(0)

menuPlane:visible(true)
	pausePlane:visible(true)
	pausePlane:animPlay("PauseAnimIn")

end


function Resume()
	
	pausePlane:animPlay("PauseAnimOut")
	menuPlane:visible(false)
	UnFreeze()

end

function UnFreeze()

	--rocketTrail:play()
	--sandTrail:play()
 playerBlender:play( idleAnimData );
 playerBlender:play( sneakAnimData );
 playerBlender:play( walkAnimData );
 playerBlender:play( runAnimData );
 playerBlender:play( jumpAnimData );

 playerBlender:play( idleHoverAnimData );
 playerBlender:play( runHoverAnimData );

end

function GameOver()

	playerBlender:stop(0)
	rocketTrail:stop()
	menuPlane:visible(true)
	gameOverPlane:visible(true)
	gameOverPlane:animPlay("GameOverAnimIn")

end

function Succeed()
	playerBlender:stop(0)
	rocketTrail:stop()
	menuPlane:visible(true)
	succeedPlane:visible(true)
	succeedPlane:animPlay("SucceedAnimIn")


end

function SelectMenu(menuType, indice, selected)



	if menuType == "MainMenu" then 
		if selected == false 
			then   UnselectButton(mainMenu[indice])
			else   SelectButton(mainMenu[indice])
		end

	elseif menuType == "PauseMenu" then

	
		if selected == false 
			then   UnselectButton(pauseMenu[indice])
			else  SelectButton(pauseMenu[indice])
		end


	elseif menuType == "LevelSelectMenu" then
			if selected == false 
				then   UnselectButton(levelSelectMenu[indice])
				else  SelectButton(levelSelectMenu[indice])
			end
		
	elseif menuType == "WinMenu" then
			if selected == false 
				then   UnselectButton(winMenu[indice])
				else  SelectButton(winMenu[indice])
			end

	elseif menuType == "GameOverMenu" then
			if selected == false 
				then   UnselectButton(gameOverMenu[indice])
				else  SelectButton(gameOverMenu[indice])
			end



	end





end

function lerp( a, b, weight )
	return a+(b-a)*weight;
end



function CreateMenu(menuType, text, indice, selected, posX, posY)
	


	if menuType == "MainMenu" then 
		mainMenu[indice] = Mesh.createText{ str=text, style=unselectedMenuStyle, pos=Vector(0,1 - indice /2.5 ,0), overlay=false }
		mainMenu[indice]:position(menu3dEmplacement:worldPosition()   )
		mainMenu[indice]:translate(Vector(0, -0.5 * (indice-1) - 0.5, 0) )  

		mainMenu[indice]:rotation(menu3dEmplacement:rotation()   )
	mainMenu[indice]:shader():setPriority(9)
	    if indice == 1 then  SelectButton(mainMenu[indice]) else UnselectButton(mainMenu[indice]) end
	
	elseif menuType == "PauseMenu" then
		pauseMenu[indice] = Mesh.createText{ str=text, style=unselectedMenuStyle, pos=Vector(0,0 - indice /5,0), overlay=true }
	pauseMenu[indice]:shader():setPriority(9)


		if indice == 1 then  SelectButton(pauseMenu[indice]) else UnselectButton(pauseMenu[indice]) end
	
	elseif menuType == "LevelSelectMenu" then
		
		levelSelectMenu[indice] = Mesh.createText{ str=text, style=unselectedMenuStyle, pos=Vector(0,1 - indice /2.5,0), overlay=false }
		levelSelectMenu[indice]:position(menu3dEmplacement:worldPosition()   )
		levelSelectMenu[indice]:translate(Vector(0, -0.5 * (indice-1) - 0.5, 0) )  
		levelSelectMenu[indice]:rotation(menu3dEmplacement:rotation()   )

		if indice == 1 then  SelectButton(levelSelectMenu[indice]) else UnselectButton(levelSelectMenu[indice]) end
	
	elseif menuType == "WinMenu" then
		winMenu[indice] = Mesh.createText{ str=text, style=unselectedMenuStyle, pos=Vector(0,0 - indice /5,0), overlay=true }
		winMenu[indice]:shader():setPriority(9)

		if indice == 1 then  SelectButton(winMenu[indice]) else UnselectButton(winMenu[indice]) end
	
	elseif menuType == "GameOverMenu" then
		gameOverMenu[indice] = Mesh.createText{ str=text, style=unselectedMenuStyle, pos=Vector(0,0 - indice /5,0), overlay=true }
		gameOverMenu[indice]:shader():setPriority(9)

		if indice == 1 then  SelectButton(gameOverMenu[indice]) else UnselectButton(gameOverMenu[indice]) end
	end

end


function StarterPicked()



DisplayEgg(true)
SetRunCamera()

end

function LoadLevel(name, device)

	destDevice = device
	merge(name)
	sandShader =  Shader.find("sandShader")


	sunLight = Light.find("defaultSunLight")


	sunLight:setAttr {	mDiffuseColor=Vector(1,1,1,1),						mAmbientColor=Vector(0.1,0.1,0.1,1),  					mType=0}	
	sunLight:rotation(-75,0,0)

	backLight = Light.find("defaultBackLight")

	backLight:setAttr {	 mDiffuseColor=Vector(0.25,0.25,0.25,1)	,					 mAmbientColor=Vector(0.01,00.1,0.1,1), 					 mType=0}	
	backLight:rotation(90,-45,0)

	offeringHud:animPlay("OfferingIdle", true)

	titleTransform:visible(false)

	camera:range( 0.5, 10000 )
	playerBlender:spacePos( idlePosition )
	SetWalkCamera()
	UpdateCamera()
	UnFreeze()

	EnableRocketTrail(false)
	EnableRocketTrail(false)

sandTrail:stop()
rocketTrail:stop()




	if destDevice == "PC" then

		groundMesh = Mesh.find("GroundPC")
		groundHeight = groundMesh:position().y
		Mesh.find("GroundPSP"):release()
	Transform.find("GroundPSP2"):release()

	elseif destDevice == "PSP" then
		
		groundMesh = Mesh.find("GroundPC")
		groundHeight = groundMesh:position().y
		groundMesh:release()
		Mesh.find("GroundPSP"):release()

	   sandShader:setPriority(6)
		layerCollision = Layer.find("Collision")	




	end

	--sandShader:textureTransform(0,0,0,0,scaleSandShaderPass1,scaleSandShaderPass1)	
	--sandShader:textureTransform(1,0,3,0,scaleSandShaderPass2,scaleSandShaderPass2)	

	CreateArea(32)


end

function ClearScene()


	for i = 1 , columnCount do
		columnList[i]:release()
	end
	columnCount = 0

	for i = 1 , areaCount do
		areaList[i]:release()
		areaLogoList[i]:release()
	end
	areaCount = 0
	areaLogoCount = 0

	worldMap = Transform.find("worldMap")

	if worldMap ~= nil then
		worldMap:release()
	else 
		print ("WorldMap not found") 
	end

	menuPlane:visible(false)
	gameOverPlane:animPlay("GameOverAnimOut")
	pausePlane:animPlay("PauseAnimOut")
	succeedPlane:animPlay("SucceedAnimOut")

	DisplayEgg(false)
	playerBlender:spacePos( idlePosition )

end


function UpdateCloud(   )
	textOffset = textOffset + 0.0005
	sandShader:textureTransform(2,0,textOffset,textOffset,1,1)	


end

function PlayerSetPosition(posX, posY, posZ,  angle, state)

playerTransform:position(Vector(posX, groundHeight + posY, posZ)  )
playerTransform:rotation(0,math.deg(angle),0)

if(destDevice == "PSP") then



	found, intersection = layerCollision:intersectRay(playerTransform:worldPivot()+Vector(0,10,0), Vector(0,-1e10,0))



	if found == true then
		playerTransform:worldPivot(intersection)
		playerTransform:translate(Vector(0,posY,0))
	end

end




	--sandTrail:position(playerTransform:position())
	
--	sandTrail:rotation(playerTransform:rotation())
	--sandTrail:preTranslate(Vector(0,2,0))
--	rocketTrail:position( rocket:worldPosition() )
--	rocketTrail:rotation(playerTransform:rotation())





UpdateCloud()

end

function UpdateParticles(state, thrustSpeed, thrustMaxSpeed, speed,  speedAngle)


	if(state=="Walking") then




			EnableRocketTrail(false)
			EnableSandTrail(false)

	

	else


			EnableRocketTrail(true)
			EnableSandTrail(true)


	end



	
	sandTrail:position(playerTransform:position())


	sandTrail:rotation( Vector(0,math.deg(speedAngle ) +45, 0  )    )


end




function WormHeadPosition(posX, posY, posZ,  angle)

wormRoot:position(Vector(posX, groundHeight +1.5, posZ))

wormHead:position(Vector(posX, groundHeight +1.5, posZ) - wormRoot:position()  )


wormHead:rotation(0,math.deg(angle),0)

screenRatio = 480/272


screenPos = camera:worldToScreen(wormRoot:position() - wormHead:position()  ) 
screenPos.x = screenPos.x* screenRatio

pixelOffset = 0.3


	if  screenPos.x  >-1  * screenRatio and screenPos.x  <1  * screenRatio and screenPos.y  >-1 and screenPos.y  <1      then 


	warningLogo:visible(false) 


	else 
		warningLogo:position(Vector(0.5,0.5) )
	

		warningLogo:visible(true) 

		posX  = screenPos.x 
		posY  = screenPos.y  
	
		  if screenPos.x   < -1 * screenRatio   then posX = -1 *screenRatio 

		  elseif
		     screenPos.x  >  1 * screenRatio     then posX =  1 *screenRatio 


		 end

		  if screenPos.y < -1   then posY = -1  
		    elseif	screenPos.y > 1   then posY = 1  end

		posX  = posX * 0.90
		posY = posY * 0.80


		rotateArrowAxis:rotation(Vector(0,0,90))
		warningLogo:position( Vector(posX, posY)  )


		arrowToWorm =   screenPos - warningLogo:position() 

		angle = math.atan2(arrowToWorm.y, arrowToWorm.x)
		rotateArrowAxis:rotation(Vector(0,0,  math.deg (angle) - 45 - 20 ))
	end

end



function WormTailPosition(id, posX, posY, posZ,  angle)

tailList[id+1]:position(Vector(posX, groundHeight +1.5, posZ)   -  wormRoot:position()  )
tailList[id+1]:rotation(0,math.deg(angle),0)


end
	--wormRoot:animPlay("IdleWorm", true)

function WormIdlePlay()

	if  wormRoot:animPlaying() == false then
		wormRoot:animPlay("IdleWorm", true)


	end

end

function WormOpenJaw()
	wormRoot:animPlay("OpenJaw", false)

end

function WormCloseJaw()


	wormRoot:animPlay("CloseJaw", false)
	
end





function CreateWorm()	

	tailCount = LuaGetTailCount()

	radius = LuaGetWormRadius()

	wormHead = Mesh.createSphere(radius, Vector(1,0,0,1))

	posX, posY, angle = LuaGetWormHeadParams()

	wormHead:position(posX,0,- posY)
	wormHead:rotation(angle)
	headJoint:position(posX,0, - posY)

	for i = 1, tailCount do

	tTailList[i] = Mesh.createSphere(radius)
	posX, posY, angle = LuaGetWormTailParams(i)
	tTailList[i]:position(posX, 0, -posY)
	tTailList[i]:rotation(angle)

	end
end


function CreateMap()
	iWallCount = LuaGetWallCount()

	

	for i = 1, iWallCount do
	posX, posY, sizeX,sizeY = LuaGetWall(i)


	tWallList[i] = Mesh.createBox( sizeX, 3,sizeY )
	tWallList[i]:position(Vector(posX, 0, -posY))

 	end

end


function ClearWorld() 
	curworld = World.getActive()
	curworld.clear()
end

