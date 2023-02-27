# ue5-cardgame

Card game plugin for Unreal Engine 5.

Note: This document is work-in-progress and subject to change.

## Goals

* Common Gameplay Features
* Blueprint API
* Networking
* Automated Tests
* Savegames
* Auto AI
* Diagnostics
* Simplicity
* Documentation

## Plugin Setup

1. Close your Unreal Editor.
1. Download the latest release.
1. Copy the CardGame folder to the Plugins folder next to your .uproject file (create if necessary).
1. Start the Unreal Editor.

## Usage

### Data

1. Add data assets of class CardGameCard.
1. Add data assets of class CardGameCardPile.
1. Add data assets of class CardGameAttribute.
1. Add a data asset of class CardGameConfiguration.
1. Add a (blueprint) class with parent class CardGameActor and implement Init.
1. Add a (blueprint) class with parent class CardGameActorManager and set Card Actor Class.
1. Add a (blueprint) class with parent class CardGamePlayerController and set Actor Manager Class.
1. Add a (blueprint) class with parent class CardGameMode and set Configuration and Player Controller Class.

### Game Setup

1. Using the Card Pile Subsystem, add cards to player piles, shuffle them and/or move cards betweem them.
1. Using the Attribute Subsystem, set global and player attribute values.
1. In your card game mode, call Start Game.

## Structure

* Assets: Unreal assets (`Blueprintable UObject`s, `UDataAsset`s). No logic. Used by plugin users for creating their content.
* Model: Pure model classes. No logic. Need to be copied for Auto AI.
* Providers: Value providers (e.g. ids, random numbers). Have logic and state.
* Services: Core game logic classes. Stateless.
* Subsystems: Unreal blueprint access to services. Trivial delegate pattern.

Layers similar to traditional model/view/controller or endpoint/service/DAO: 

* PlayerController (components) = (replication) endpoints
* services = services
* providers = DAO

## Design Decisions

* Provider subsystems are used for injecting dependencies for service subsystems. These dependencies need to be available before the game mode might have been initialized.
* RPCs for efficiency, events and secrets
* Relations expressed by indices, not pointers, to allow for copying.
* Player actions are just abilities. This allows Auto AI to automatically apply them.

## Commit Checklist

* Add unit tests.
* Add detailed documentation.
