# 1.0.0
### Breaking Changes
* The `BCOVPUIControlLayoutStrategy layoutStrategy` property of the `BCOVPUIControlLayout` class has been removed in favor of a simpler method of specifying control layouts. See the sample code in README.md for details.
* The `BCOVPUIBasicControlSize` enum used by `BCOVPUIControlLayoutStrategy layoutStrategy` has been removed.
* The `BCOVPUIMutableControlLayout` class has been removed. You can now modify a layout at will, and then assign it directly to the `BCOVPUIControlView layout` property at any time. The layout will be copied upon assignment, so to enable further changes you need to assign the layout again.
* `BCOVPUIControlLayout maximumWidthOfControlSizeCompact` is now `BCOVPUIControlLayout compactLayoutMaximumWidth`.
* `BCOVPUIControlLayout preferredHeightOfControlSizeRegular` and `BCOVPUIControlLayout preferredHeightOfControlSizeCompact` have been removed. Control size can be set individually for each control.
* In the `BCOVPUIControlLayout` class, the `items` property of `BCOVPUIControlLayout` has split into `standardLayoutItems` and `compactLayoutItems`. `standardLayoutItems` are displayed unless the control view width is greater than `compactLayoutMaximumWidth` (formerly `maximumWidthOfControlSizeCompact`). Although there are two lists of items, objects can (and typcially should) be shared between them.
* In the `BCOVPUIControlLayout` class, `itemSize` is replaced by `controlBarHeight` to set the size of each row of controls. The number of installable rows of controls is unlimited, though typically one row for landscape orientation, and two rows for portrait orientation (compact view).
* In the `BCOVPUIControlLayout` class, `itemSpacing` is now called `horizontalItemSpacing`.
* `BCOVPUIControlLayout initWithItems:` is replaced by `BCOVPUIControlLayout initWithStandardControls:compactControls:`. The setup of the standard and compact layouts passed to this new method is shown in the sample code in README.md.
* `BCOVPUIControlLayout defaultAdaptiveLayoutStrategy` has been removed.
* `BCOVPUIControlLayout layoutStrategyForVideoTypeVOD` has been renamed `BCOVPUIControlLayout basicVODControlLayout` .
* `BCOVPUIControlLayout layoutStrategyForVideoTypeLive` has been renamed `BCOVPUIControlLayout basicLiveControlLayout` .
* `BCOVPUIControlLayout layoutStrategyForVideoTypeLiveDVR` has been renamed `BCOVPUIControlLayout basicLiveDVRControlLayout` .
* `BCOVPUIBasicControlView basicControlViewWithAdaptiveLayout` has been removed.
* `BCOVPUIBasicControlView`'s `currentVideoType` property has been removed.
* `BCOVPUIBasicControlView`'s `setFontSizeForLabel`, `setFontSizeForButton`, `setTextColorForLabel`, and `setTitleColorForButton:forState:` are now `setFontSizeForLabels`, `setFontSizeForButtons`, `setTextColorForLabels`, and `setTitleColorForButtons:forState:`.
* `BCOVPUIBasicControlView componentItemForBasicComponents:` and `BCOVPUIBasicControlView createUIComponentItemWithViewTag:` have been replaced by `BCOVPUIBasicControlView layoutViewWithControlFromTag:width:elasticity:` and `BCOVPUIBasicControlView createPUIControlItemWithViewTag`. UI components are now created individually and placed within a `BCOVPUILayoutView`.
* `BCOVPUIBasicControlView viewTagForBasicComponent` has been removed. See README.mb for details on control creation and usage.
* The `BCOVPUIBasicComponents` enum (use by other removed methods) has been removed.
* `kBCOVPUIControlHeightItemSize` and `kBCOVPUIControlHeightItemSizeDouble`. Control bar height is now specified by `BCOVPUIControlLayout controlBarHeight`.
* The static library distributable has been removed. If installed manually (not CocoaPods), you will need to remove libBCOVPlayerUI.a and its headers from the Header Search Path. Please see README.md for new install options (including a static library framework).
* Header `BCOVPUI.h` has been removed. Please see README.md for new import options.

### Additions and Improvements
* The Player UI plugin now offers the ability to modify layouts dynamically, hide views in existing layouts, create layouts with your own control arrangements, and even add your own views to empty layout cells.
* You can have different layouts for portrait versus landscape orientations, and set the number of rows of controls for each orientation.
* Controls in a layout can have fixed or elastic widths.
* Bitcode support.
* The SDK is now distributed as a static or dynamic framework.


# 1.0.0-beta2

### Additions and Improvements
* Internal improvements.