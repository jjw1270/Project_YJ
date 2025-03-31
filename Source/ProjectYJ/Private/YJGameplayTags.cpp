// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YJGameplayTags.h"
#include "CommonLibrary.h"
#include "GameplayTagsSettings.h"

namespace YJGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "Move input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look, "InputTag.Look", "Look input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Jump, "InputTag.Jump", "Jump input.");
}

void UTagManager::Initialize(FSubsystemCollectionBase& _collection)
{
	ValidateGameplayTags();
}

int32 UTagManager::FindInputID(const FGameplayTag& _tag) const
{
	return _GameplayTagNames.Find(_tag.GetTagName());
}

void UTagManager::ValidateGameplayTags()
{
	_GameplayTagNames.Empty();

	const auto& manager = UGameplayTagsManager::Get();

	TArray<const FGameplayTagSource*> tag_sources;
	manager.FindTagSourcesWithType(EGameplayTagSourceType::Native, tag_sources);

	for (const auto tag_source : tag_sources)
	{
		if (tag_source != nullptr)
		{
			auto source_tags = tag_source->SourceTagList;
			if (IsValid(source_tags))
			{
				for (const auto& tag_row : source_tags->GameplayTagList)
				{
					_GameplayTagNames.Add(tag_row.Tag);
				}
			}

			auto source_restricted_tags = tag_source->SourceRestrictedTagList;
			if (IsValid(source_restricted_tags))
			{
				for (const auto& tag_row : source_restricted_tags->RestrictedGameplayTagList)
				{
					_GameplayTagNames.Add(tag_row.Tag);
				}
			}
		}
	}
}
