# GMTK2023

## Useful Links

* Game Design Document: https://docs.google.com/document/d/1Xl2C9m4MS_1AS-UlLXeUqAjiBPxlUKWhyZCcEHrPPtk/edit?usp=sharing
* Trello: https://trello.com/invite/b/ok8dI90w/ATTI5eb7f25ece737968711251cea9b6c5515E433646/gmtk-2023

## Style Guidelines

This link gives is useful for knowing where to put project files and naming conventions to keep things organized. https://github.com/Allar/ue5-style-guide/tree/v2

### TLDR:

* Add comments and descriptions.

* Prefix assets with their type (i.e. `M_Bob` for a material called Bob).

* Use PascalCase for folder names, variables, and functions. The one exception this is if a blueprint variable is a boolean, in which case it should be started with a `b` (i.e. `bDead` ).

* Have functions start with verbs (i.e. `Jump` or `ReceiveMessage`), unless they're booleans, in which case they should ask a question like `IsDead`.
