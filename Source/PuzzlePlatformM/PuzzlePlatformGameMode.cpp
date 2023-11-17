// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameMode.h"
#include "Json.h"

APuzzlePlatformGameMode::APuzzlePlatformGameMode()
{
}

void APuzzlePlatformGameMode::StartPlay()
{
    Super::StartPlay();

    //CustomHTTPRequest();
}

void APuzzlePlatformGameMode::CustomHTTPRequest()
{
     FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

    //Code below is for POST requests
    // TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
    // RequestObj->SetStringField("title", "foo");
    // FString RequestBody;
    // TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    // FJsonSerializer::Serialize(RequestObj, Writer);
    //Code above is for POST requests

	Request->OnProcessRequestComplete().BindUObject(this, &APuzzlePlatformGameMode::OnResponseReceived);
    Request->SetURL("http://18.191.242.14:8080/test");
	//Request->SetURL("https://jsonplaceholder.typicode.com/posts/1"); //GET method
    //Request->SetURL("https://jsonplaceholder.typicode.com/posts"); //POST method
	Request->SetVerb("GET"); //GET method
    //Request->SetVerb("POST"); //For Post
    //Request->SetHeader("Content-Type", "application/json"); //For Post
    //Request->SetContentAsString(RequestBody); //For Post
	Request->ProcessRequest();
};

void APuzzlePlatformGameMode::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    TSharedPtr<FJsonObject> ResponseObj; //Create ResponseObj
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString()); //Create Reader
    FJsonSerializer::Deserialize(Reader, ResponseObj); //Deserialize

    UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString()); //Print Response
    //UE_LOG(LogTemp, Warning, TEXT("Title: %s"), *ResponseObj->GetStringField("title")); //Print specific item
}


