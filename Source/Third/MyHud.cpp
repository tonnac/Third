// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHud.h"

#include "ThirdCharacter.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Components/Button.h"

void UMyHud::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayButton->OnClicked.AddDynamic(this, &UMyHud::OnClicked_Button);
}

void UMyHud::OnClicked_Button()
{
	if (bPlayMontage)
	{
		// SkeletalMeshComponent->Stop();
		AnimInstance->Montage_Play(AnimMontage);
		
		// UAnimMontage* NewMontage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(AnimMontage, FAnimSlotGroup::DefaultSlotName, 0.25f, 0.25f, 1.f, 1, -1.f, 0.f);
		// float PlayTime = AnimInstance->Montage_Play(NewMontage, 1, EMontagePlayReturnType::MontageLength, 0.f);
	}
	else
	{
		const float SequenceLength = AnimMontage->SequenceLength;
		if (GetWorld() && SequenceLength > 0.f)
		{
			FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			if (TimerHandle.IsValid())
			{
				TimerManager.ClearTimer(TimerHandle);
			}
			TimerManager.SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &UMyHud::OnMontageEnd), SequenceLength - DecreaseTime, false);
			SkeletalMeshComponent->PlayAnimation(AnimMontage, false);
		}
	}
}

void UMyHud::SetCharacter(AThirdCharacter* ThirdCharacter)
{
	Character = ThirdCharacter;
	check(Character.IsValid());
	
	SkeletalMeshComponent = Character->FindComponentByClass<USkeletalMeshComponent>();
	check(SkeletalMeshComponent.IsValid());
	
	// SkeletalMeshComponent->PlayAnimation(AnimSequence, true);
	SkeletalMeshComponent->OverrideAnimationData(AnimSequence);

	AnimInstance = Cast<UAnimSingleNodeInstance>(SkeletalMeshComponent->GetAnimInstance());
	check(AnimInstance.IsValid());
	AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UMyHud::OnMontageEnd);
}

void UMyHud::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (CreatedMontage == Montage)
	{
		// SkeletalMeshComponent->PlayAnimation(AnimSequence, true);
	}
}

void UMyHud::OnMontageEnd()
{
	if (SkeletalMeshComponent.IsValid())
	{
		// SkeletalMeshComponent->PlayAnimation(AnimSequence, true);
		
		CreatedMontage = AnimInstance->PlaySlotAnimationAsDynamicMontage(AnimSequence, FAnimSlotGroup::DefaultSlotName, 0.25f, 0.25f, 1, TNumericLimits<int32>::Max());
	}
}
