# Warptex Engine
This was originally a Year 2 University Project that I have since majorly refactored and decided to re-publish.
It is a basic C++-based SDL2 setup for making Bullet Hell Patterning and Gameplay, designed to be somewhat
flexible with configurable pattern generation, loading pattern designs from dat files.

Not all features have been ported or refactored yet, so a lot of features are currently missing.
### Currently reimplementing:
- Menu Functionality
- Lives, Game Over

### I would like to implement:
- Improved collision tag matrix for determining which objects can collide with one-another.
- Scheduling system for tasks
- Parallelisation to further improve performance with loads of objects

### Long Term:
- Enemy object that hurt on contact and can spawn projectiles
- Level loading via menu
- Flexible UI system
- Some way to dynamically load game assets
- Render optimisations
- More precise collision than simply image overlap
- Defining collision zones as different than the sprite surface
