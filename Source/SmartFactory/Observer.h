// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Observer.generated.h"

class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWidgetClicked, UUserWidget*, InWidget);

UCLASS(BlueprintType)
class SMARTFACTORY_API UObserver : public UObject
{
	GENERATED_BODY()
	

	// singleton
public:
	virtual ~UObserver();
	UFUNCTION(BlueprintCallable, meta=(AllowPrivateaccess=true))
	static UObserver* GetObserver();

private:
	static UObserver* Instance;



	// feature
public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWidgetClicked OnWidgetClicked;

	void subscribe();

	void Callback(UUserWidget* InWidget);
};
