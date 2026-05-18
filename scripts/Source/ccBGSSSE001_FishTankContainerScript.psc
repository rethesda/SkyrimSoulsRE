scriptName ccBGSSSE001_FishTankContainerScript extends ObjectReference

message property notAllowedFishMsg auto
{Message displayed when the player places a non-fish form (or the wrong size of fish) in the container.}
keyword property ccBGSSSE001_FishTankMarkerKW02 auto
{The keyword corresponding to the second fish tank fish marker.}
message property fishTankFirstTimeMsg auto
{Display message when a fish tank of this size is used for the first time. Only displays once.}
formlist property placeableFishList auto
{The list of inventory items that can be placed in this tank.}
keyword property ccBGSSSE001_FishTankMarkerKW03 auto
{The keyword corresponding to the third fish tank fish marker.}
message property ccBGSSSE001_fishTankHostileFishMsg auto
{Message displayed when the player places a hostile fish form (i.e. Slaughterfish) in the container.}
Int property maxFishAllowed
	Int function get()
		return 3
	endFunction
endproperty
keyword property ccBGSSSE001_FishTankMarkerKW01 auto
{The keyword corresponding to the first fish tank fish marker.}
globalvariable property fishTankActivated auto
{Tracks whether or not the player has ever activated a fish tank of this size.}
message property ccBGSSSE001_fishTankRoomLeftMsg auto
{Notification that tells the player how much room is left in the fish tank.}
message property ccBGSSSE001_fishTankNoMoreRoomMsg auto
{Message displayed when the amount of fish in the tank would exceed the tank limit.}
formlist property placeableFishActivatorList auto
{The list of corresponding swimming fish activators for each inventory item.}
formlist property hostileFishList auto
{The list of inventory items of hostile fish.}
ccBGSSSE001_FishTankCritterScript placedFishRef01
Activator placedFishForm03
Bool queuedUpdate = false
Bool skipRemovalProcessing = false
Activator placedFishForm02
ccBGSSSE001_FishTankCritterScript placedFishRef03
ccBGSSSE001_FishTankCritterScript placedFishRef02
Activator placedFishForm01
Int currentFishCount = 0
function UpdateFish()
	GotoState("UpdatingFish")
	if Is3DLoaded()
		placedFishRef01 = UpdateSingleFish(placedFishForm01 as Form, placedFishRef01, GetLinkedRef(ccBGSSSE001_FishTankMarkerKW01))
		placedFishRef02 = UpdateSingleFish(placedFishForm02 as Form, placedFishRef02, GetLinkedRef(ccBGSSSE001_FishTankMarkerKW02))
		placedFishRef03 = UpdateSingleFish(placedFishForm03 as Form, placedFishRef03, GetLinkedRef(ccBGSSSE001_FishTankMarkerKW03))
	else
		queuedUpdate = true
	endIf
	GotoState("")
endFunction

function OnItemRemoved(Form akBaseItem, Int aiItemCount, ObjectReference akItemReference, ObjectReference akDestContainer)
	if placeableFishList.HasForm(akBaseItem)
		if !skipRemovalProcessing
			RemoveFish(akBaseItem, aiItemCount)
			currentFishCount -= aiItemCount
		else
			skipRemovalProcessing = false
		endIf
	endIf
endFunction

function OnItemAdded(Form akBaseItem, Int aiItemCount, ObjectReference akItemReference, ObjectReference akSourceContainer)
	if placeableFishList.HasForm(akBaseItem)
		if aiItemCount + currentFishCount <= maxFishAllowed
			AddFish(akBaseItem, aiItemCount)
			currentFishCount += aiItemCount
		else
			ccBGSSSE001_fishTankNoMoreRoomMsg.Show()
			skipRemovalProcessing = true
			RemoveItem(akBaseItem, aiItemCount, true, game.GetPlayer() as ObjectReference)
		endIf
	else
		if hostileFishList.HasForm(akBaseItem)
			ccBGSSSE001_fishTankHostileFishMsg.Show()
		else
			notAllowedFishMsg.Show()
		endIf
		RemoveItem(akBaseItem, aiItemCount, true, game.GetPlayer() as ObjectReference)
	endIf
endFunction

function MakeFishPanic()
	if placedFishRef01
		placedFishRef01.TryToMoveToNextMarker(true)
	endIf
	if placedFishRef02
		placedFishRef02.TryToMoveToNextMarker(true)
	endIf
	if placedFishRef03
		placedFishRef03.TryToMoveToNextMarker(true)
	endIf
endFunction

function RemoveFish(Form akFish, Int fishCount)
	Activator fishActivator = placeableFishActivatorList.GetAt(placeableFishList.Find(akFish)) as Activator
	if !fishActivator
		return 
	endIf
	while fishCount > 0
		if placedFishForm01 == fishActivator
			placedFishForm01 = none
		elseIf placedFishForm02 == fishActivator
			placedFishForm02 = none
		elseIf placedFishForm03 == fishActivator
			placedFishForm03 = none
		endIf
		fishCount -= 1
	endWhile
endFunction

ccBGSSSE001_FishTankCritterScript function UpdateSingleFish(Form targetFish, ccBGSSSE001_FishTankCritterScript placedFishRef, ObjectReference targetMarker)
	ccBGSSSE001_FishTankCritterScript returnFishRef
	if placedFishRef
		placedFishRef.StopPathing()
		placedFishRef.Disable()
		placedFishRef.Delete()
	endIf
	if targetFish
		returnFishRef = targetMarker.PlaceAtMe(targetFish, 1, false, false) as ccBGSSSE001_FishTankCritterScript
		returnFishRef.StartPathing(targetMarker)
		while !returnFishRef.Is3DLoaded()
			utility.Wait(0.100000)
		endWhile
		returnFishRef.SetScale(0.750000)
		utility.Wait(utility.RandomFloat(0.000000, 0.300000))
	endIf
	return returnFishRef
endFunction

function AddFish(Form akFish, Int fishCount)
	Activator fishActivator = placeableFishActivatorList.GetAt(placeableFishList.Find(akFish)) as Activator
	if !fishActivator
		return 
	endIf
	while fishCount > 0
		if !placedFishForm01
			placedFishForm01 = fishActivator
		elseIf !placedFishForm02
			placedFishForm02 = fishActivator
		elseIf !placedFishForm03
			placedFishForm03 = fishActivator
		endIf
		fishCount -= 1
	endWhile
endFunction

function OnActivate(ObjectReference akActionRef)
	ccBGSSSE001_fishTankRoomLeftMsg.Show((maxFishAllowed - currentFishCount) as Float, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000)
	if fishTankActivated.GetValueInt() == 0
		fishTankFirstTimeMsg.Show()
		fishTankActivated.SetValue(1 as Float)
	endIf
	Activate(game.GetPlayer() as ObjectReference, true)
	while(Utility.IsInMenuMode())
		utility.Wait(0.250000)
	endwhile
	UpdateFish()
endFunction

function OnLoad()
	if queuedUpdate
		queuedUpdate = false
		UpdateFish()
	endIf
endFunction

state UpdatingFish

	function UpdateFish()
		; Empty function
	endFunction
endState