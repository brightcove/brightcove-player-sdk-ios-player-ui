# BCOVPlayerUI Plugin for Brightcove Player SDK for iOS, version 1.0.4.143

Supported Platforms
===================

iOS 7.0 and above.

Installation
============
The Brightcove PlayerUI Plugin provides two installation packages for iOS, a static library framework and a dynamic framework. The static library target supports deployment on iOS 7 while the dynamic framework only supports iOS 8 and above.

CocoaPods
--------------

You can use [CocoaPods][cocoapods] to add the PlayerUI Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-SDK-Player-UI` podspec [here][podspecs].

Static Framework example:

    pod 'Brightcove-Player-SDK-Player-UI'
    
Dynamic Framework example:

    pod 'Brightcove-Player-SDK-Player-UI/dynamic'

Manual
--------------

To add the PlayerUI Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
2. Download the latest zipped release of the plugin from our [release page][release].
3. Add the 'BrightcovePlayerUI.framework' to your project.
4. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the path to the framework. This should have been done automatically unless the framework is stored under a different root directory than your project.
5. On the "Build Phases" tab of your application target, add the following to the "Link Binary With Libraries" phase:
    * `BrightcovePlayerUI.framework`
6. (Dynamic Framework only) On the "General" tab of your application target, add 'BrightcovePlayerUI.framework' to the "Embedded Binary" section.
7. (Dynamic Framework only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcovePlayerUI.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission. ([rdar://19209161][19209161])
8. (Static Framework only) On the "Build Settings" tab of your application target, add `-ObjC` to the "Other Linker Flags" build setting.
9. (Static Framework only) Add the file `bcovpuiiconfont.ttf` from the `BrightcovePlayerUI.framework` bundle directly to your project listing so that the font file is copied into the app bundle. In the end, the font file should end up at the same level as the app's `Info.plist` file. The font file supplies some of the BrightcovePlayerUI interface elements, but it does not need to be listed in the plist itself.

Imports
--------------
The Brightcove Player SDK for iOS can be imported into code a few different ways; `@import BrightcovePlayerUI;`, `#import <BrightcovePlayerUI/BrightcovePlayerUI.h>` or `#import <BrightcovePlayerUI/[specific class].h>`.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/CocoaPods/Specs/tree/master/Specs/Brightcove-Player-SDK-Player-UI
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-player-ui/releases
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

Quick Start
===========
Its use is relatively straightforward. This example creates a basic layout suitable for general on-demand video streams:

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    [1] id<BCOVPlaybackController> controller = [manager createPlaybackController];
        
    [2] BCOVPUIPlayerView *playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:playbackController];
        playerView.frame = self.videoContainer.bounds;
        playerView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
        [self.videoContainer addSubview:playerView];
        
    [3] NSString *token;      // (Brightcove Media API token with URL access)
        NSString *playlistID; // (ID of the playlist you wish to use)
        BCOVCatalogService *catalog = [[BCOVCatalogService alloc] initWithToken:token];
        [catalog findPlaylistWithPlaylistID:playlistID
                                 parameters:nil
                                 completion:^(BCOVPlaylist *playlist,
                                              NSDictionary *jsonResponse,
                                              NSError      *error) {

            [controller setVideos:playlist];
            [controller play];

        }];

Let's break this code down into steps, to make it a bit simpler to digest:

1. Create a playback controller with its default settings.
2. Create a player view using the playback controller. This will instantiate a player view with its default settings. Set the player view to match the size of your video container view.
3. Retrieve and play a video.

Customizing Plugin Behavior
===========================
The BCOVPlayerUI plugin provides an easy out of the box experience. However, it's possible to change the default behavior.

BCOVPUIPlayerViewOptions
----------------------
The `BCOVPUIPlayerViewOptions` class allows you to customize some BCOVPlayerUI behavior at initialization. You can customize:

* `jumpBackInterval` The time in seconds the player will jump back when the jump back button is pressed.  
* `hideControlsInterval` The time in seconds after the last touch event, before the controls are hidden.  
* `hideControlsAnimationDuration` The time in seconds it takes for the controls to animate to hidden.  
* `showControlsAnimationDuration` The time in seconds it takes for the controls to animate to visible.  
* `presentingViewController` The view controller to use for presenting things like modals and fullscreen.

Options can be set using the following method:

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackController];

        BCOVPUIPlayerViewOptions *options = [[BCOVPUIPlayerViewOptions alloc] init];
        options.jumpBackInterval = 5;
     
        BCOVPUIPlayerView *playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:playbackController options:options];

Supplied Layouts
----------------------
Three layouts are provided to support different types of video:

- `BCOVPUIControlLayout basicVODControlLayout` is a basic layout for general on-demand video streams.

- `BCOVPUIControlLayout basicLiveControlLayout` is a layout targeted towards live video.

- `BCOVPUIControlLayout basicLiveDVRControlLayout` is targeted towards live video streams with DVR controls.

You typically set a new layout immediatley after your `BCOVPUIPlayerView` is created, but you can also set a new layout at any time. For example, you can set a new VOD layout like this:

	playerview.controlView.layout = [BCOVPUIControlLayout basicVODControlLayout]

Custom Layouts
----------------------

In addition to the default layouts, you can create your own highly customized layouts by instantiating a new `BCOVPUIControlLayout` with your own design.

First, create the controls that will go in your layout using `BCOVPUIBasicControlView layoutViewWithControlFromTag:width:elasticity:`. Each control is packaged in a `BCOVPUILayoutView` that determines the control spacing. You can set the `width` of each layout view to the default width (which is based on the type of control), or you can specify your own width.

The `elasticity` argument determines how much the layout view containing the control reizes its width to fill the control bar. An elasticity of zero means the size of the layout view will be fixed. An elasticity value greater than zero determines how much the layout view will grow to fill available space relative to all other elastic views in that control bar. A layout view with an elasticity value of 2.0 will grow twice as fast as a layout view with an elasticity value of 1.0. Typically a row of layout views will have at least one control with an elasticity greater than zero.

Here are examples of creating a variety of basic controls.

    BCOVPUILayoutView *playbackLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonPlayback                   width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];
    
    BCOVPUILayoutView *jumpBackButtonLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonJumpBack width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

    BCOVPUILayoutView *currentTimeLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagLabelCurrentTime width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

    BCOVPUILayoutView *timeSeparatorLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagLabelTimeSeparator width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

    BCOVPUILayoutView *durationLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagLabelDuration      width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];
                                                                                       
    BCOVPUILayoutView *progressLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagSliderProgress width:kBCOVPUILayoutUseDefaultValue elasticity:1.0];
                                                                                       
    BCOVPUILayoutView *closedCaptionLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonClosedCaption width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];
    
    BCOVPUILayoutView *screenModeLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonScreenMode width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

    BCOVPUILayoutView *externalRouteLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewExternalRoute width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

    BCOVPUILayoutView *spacerLayoutView1 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:1.0 elasticity:1.0];

    BCOVPUILayoutView *spacerLayoutView2 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:1.0 elasticity:1.0];

    BCOVPUILayoutView *logoLayoutView1 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:80.0 elasticity:1.0];
    
    BCOVPUILayoutView *logoLayoutView2 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:36.0 elasticity:0.0];

    // Hide closed caption and AirPlay controls until explicily needed.
    closedCaptionLayoutView.removed = YES;
    externalRouteLayoutView.removed = YES;

Note that you can also create an empty layout view, into which you can place your own view (logo, control, nothing, etc.). This code shows how to place a UIImage logo inside the logoLayoutView1 we created above.

    // Create logo image inside an image view for display in control bar.
    UIImage *logoImage1 = [UIImage imageNamed:@"myLogo"];
    UIImageView *logoImageView1 = [[UIImageView alloc] initWithImage:logoImage1];

    logoImageView1.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    logoImageView1.contentMode = UIViewContentModeScaleAspectFit;
    logoImageView1.frame = logoLayoutView1.frame;

    // Add image view to our empty layout view.
    [logoLayoutView1 addSubview:logoImageView1];

Now that we have a collection of controls packaged in layout views, we can order them into arrays, each of wihch represents a single line of controls, i.e. a control bar. Note that you can have different layouts for portrait and landscape orientations, so you will typically set up two different arrays of control bars.

In this standard layout for landscape orientation, we will arrange our controls in a single line, and then put that array into another array representing the entire confiuration.

            NSArray *standardLayoutLine1 = @[ playbackLayoutView, jumpBackButtonLayoutView, currentTimeLayoutView, timeSeparatorLayoutView, durationLayoutView, progressLayoutView, spacerLayoutView1, logoLayoutView1, spacerLayoutView2, closedCaptionLayoutView, screenModeLayoutView, externalRouteLayoutView ];
            NSArray *standardLayoutLines = @[ standardLayoutLine1 ];

In the compact layout, for portrait orientation, we create two arrays of controls, and then those two arrays are packaged into another array representing the compact layout.

Note that we used the exact same objects for most of the controls in each layout. When this is done, and you switch between portrait and landscape orientations, the object will be moved to its new position using smooth animation.


            NSArray *compactLayoutLine1 = @[ currentTimeLayoutView, progressLayoutView, durationLayoutView ];
            NSArray *compactLayoutLine2 = @[ playbackLayoutView, jumpBackButtonLayoutView, spacerLayoutView1, closedCaptionLayoutView, screenModeLayoutView, externalRouteLayoutView, logoLayoutView2 ];
            NSArray *compactLayoutLines = @[ compactLayoutLine1, compactLayoutLine2 ];

Finally, now that we have two layout configurations, one for full width, and one for compact width, we can create a new `BCOVPUIControlLayout` object, and set it in the player's control view.

            BCOVPUIControlLayout *customLayout = [[BCOVPUIControlLayout alloc] initWithStandardControls:standardLayoutLines compactControls:compactLayoutLines];
			playerView.controlView.layout = customLayout;

If you have controls that you need to show or hide frequently, you can set the `removed` property on that control's layout view. When you have changed your controls, call `setNeedsLayout` on the playerView's controlView:

		logoLayoutView1.removed = YES;
	    [playerView.controlsView setNeedsLayout];

You can also customize several general `BCOVPUIControlLayout` properties:

- `controlBarHeight` sets the size of each row of controls.
- `horizontalItemSpacing` sets the spacing between each `BCOVPUILayoutView` in each control bar.
- `compactLayoutMaximumWidth` determines which set of controls is used. If the control view is smaller than `compactLayoutMaximumWidth`, the compact control set will be used, otherwise the standard controls will be used.

To change the set of controls that are displayed, you must create and install a new `BCOVPUIControlLayout`.

Frequently Asked Questions
==========================

** Does this work with all Brightcove Player SDK plugins? **

This release support basic VOD, Live, and Live DVR playback without advertising. We will add support for other plugins in future releases.

** How can I customize properties other than those mentioned above?**

Our goal is to create something that's easy to customize, while still providing a lot of functionality and behavior out of the box. In upcoming releases, we will be covering more customization with new APIs and more documentation. If there is a feature you are looking for, please let us know in our forum.

** Will there be breaking API changes in the future versions? **

We will do our best not to change things unless we really need to. However, if we do need to make API changes, we will provide clear migration steps in the CHANGELOG.


