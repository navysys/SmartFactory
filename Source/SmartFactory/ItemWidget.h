// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ItemWidget.generated.h"


class UTextBlock;

UCLASS()
class SMARTFACTORY_API UItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TreeItem")
	TArray<UItemWidget*> Children;

	FString NodeID;

	AActor* Actor;
};
