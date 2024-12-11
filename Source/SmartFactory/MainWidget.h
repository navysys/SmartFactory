// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UButton;
class UTreeView;
class UItemWidget;

UCLASS()
class SMARTFACTORY_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void SettingButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();

	UFUNCTION()
	void HomeButtonClicked();

	UFUNCTION()
	void AlarmButtonClicked();

	void CreateTreeItem(int Index, int ChildIndex, AActor* OwningActor = nullptr);
	void GetChildrenForItem(UObject* InItem, TArray<UObject*>& OutChildren);
	void AddChildToItem(UItemWidget* ParentItem, UItemWidget* NewChildItem);
	void OnTreeViewItemClicked(UObject* ClickedItem);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HomeButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTreeView> TreeView;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UButton> AlarmButton;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SettingPopup;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPopupModuleWidget> PopupWidget;

	//UPROPERTY(EditAnywhere)
	//TArray<UItemWidget*> RootItems;
	TArray<UItemWidget*> Items;

	bool HighLightState = false;
};
