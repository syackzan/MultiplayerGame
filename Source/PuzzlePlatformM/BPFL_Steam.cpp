// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_Steam.h"
#include "ThirdParty/Steamworks/Steamv153/sdk/public/steam/steam_api.h"

FString UBPFL_Steam::GetSteamIDByString()
{
    //Init String
    FString ReturnValue = "";

    if(SteamAPI_Init())
    {
        //Init SteamID
        uint64 SteamID = 0;

        //Store SteamID as Unique CSteamID
        CSteamID InSteamID = SteamUser()->GetSteamID();

        //Convert to 64 bit Integer
        SteamID = InSteamID.ConvertToUint64();

        if(SteamID == 0)
        {
            //If SteamID is still 0 then something failed
            ReturnValue = "Bad Steam ID";
        } else {

            //If SteamID is no longer 0, retrieval and conversion worked
            ReturnValue = FString::Printf(TEXT("%llu"), SteamID);
        }
        
    } else {

        ReturnValue = "No connection to steam initialized inside of BPFL_Steam";

    }

    return ReturnValue;
}
