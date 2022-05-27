// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHud.generated.h"

class UButton;
class AThirdCharacter;
/**
 * 
 */
UCLASS()
class THIRD_API UMyHud : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnClicked_Button();

public:
	UFUNCTION(BlueprintCallable)
	void SetCharacter(AThirdCharacter* ThirdCharacter);
	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);
	
public:
	TWeakObjectPtr<AThirdCharacter> Character = nullptr;
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;
	TWeakObjectPtr<UAnimSingleNodeInstance> AnimInstance = nullptr;
	TWeakObjectPtr<UAnimMontage> CreatedMontage = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* PlayButton = nullptr;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage = nullptr;

	UPROPERTY(EditAnywhere)
	UAnimSequence* AnimSequence = nullptr;

	UPROPERTY(EditAnywhere)
	bool bPlayMontage = false;
};
