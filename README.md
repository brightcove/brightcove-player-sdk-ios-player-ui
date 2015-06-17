# BCOVPlayerUI, Plugin for Brightcove Player SDK for iOS, version 1.0.0-beta2.69

Supported Platforms
===================

Supports iOS 7.0 and above.

Installation
============
You can use [Cocoapods][cocoapods] to add the PlayerUI Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-SDK-Player-UI` podspec [here][podspecs].

To add the PlayerUI Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
1. Download the latest zip'ed release of the plugin from our [release page][release].
1. Add the contents of Library, Headers, and Resources to the project.
1. On the "Build Phases" tab of your application target, add the following to the "Link
    Binary With Libraries" phase:
    * `libBCOVPlayerUI.a`
1. On the "Build Settings" tab of your application target:
    * Ensure that BCOVPlayerUI headers are in your application's "Header Search Path".
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.
1. Add the font to your app:
    * On the "Build Phases" tab of your application target, add `bcovpuiiconfont.ttf` to your "Copy Bundle Resources"
      Phase.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/CocoaPods/Specs/tree/master/Specs/Brightcove-Player-SDK-Player-UI
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-player-ui/releases
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios


Quick Start
===========
Its use is relatively straightforward. This example creates a basic adaptive layout:

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    [1] id<BCOVPlaybackController> controller = [manager createPlaybackController];
        
    [2] BCOVPUIPlayerView *pv = [[BCOVPUIPlayerView alloc] initWithPlaybackController:playbackController];
        [self.videoContainer addSubview:pv];
        
        NSString *token;      // (Brightcove Media API token with URL access)
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

1. You create a playback controller with its default settings.
1. You create a player view using the playback controller. This will create a player view using its default settings. 

Customizing Plugin Behavior
===========================
The BCOVPlayerUI plugin aims to provide an easy out of the box experience. However, it's possible to change the default behavior.

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

    [*] BCOVPUIPlayerViewOptions *options = [[BCOVPUIPlayerViewOptions alloc] init];
        options.jumpBackInterval = 5;
     
        BCOVPUIPlayerView *pv = [[BCOVPUIPlayerView alloc] initWithPlaybackController:playbackController options:options];

Out of the Box Layouts
----------------------
Three layouts are provided out of the box to support different types of video. By default, the player view will switch to these layouts automatically depending on the type of video. However, if you know that your player will only be displaying VOD, Live, or Live DVR, you can force a specific layout. 

To force a layout, simply create a `BCOVPUIBasicControlView` instance using one of the convenience factory methods corresponding to the layout you want. Use this controls view when initializing the player view. The example below forces a live DVR layout:

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackController];

        BCOVPUIPlayerViewOptions *options = [[BCOVPUIPlayerViewOptions alloc] init];
        options.jumpBackInterval = 5;
     
    [*] BCOVPUIBasicControlView *controlsView = [BCOVPUIBasicControlView basicControlViewWithLiveDVRLayout];
        
        BCOVPUIPlayerView *pv = [[BCOVPUIPlayerView alloc] initWithPlaybackController:self.playbackController options:options controlsView:controlView];
    
Frequently Asked Questions
==========================

** Does this work with all Brightcove player sdk plugins? **

This release support basic VOD, Live, and Live DVR playback without advertising. We will other support for plugins in future releases.

** How can I customize properties other than those mentioned above?**

Our goal is to create something that's easy to customize, while still providing a lot of functionality and behavior out of the box. In upcoming releases, we will be covering more customization with new APIs and more documentation. If there is a feature you are looking for, please let us know in our forum.

** Will there be breaking API changes in the future versions? **

We will do our best not to change things unless we really need to. However, if we do need to make API changes, we will provide clear migration steps in the CHANGELOG.


