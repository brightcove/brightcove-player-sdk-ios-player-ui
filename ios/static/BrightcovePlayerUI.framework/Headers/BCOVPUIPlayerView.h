//
// BCOVPUIPlayerView.h
// BrightcovePlayerUI
//
// Copyright (c) 2015 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>


@class BCOVPUIPlayerView;
@class BCOVPUIBasicControlView;
@protocol BCOVPlaybackController;


/**
 * States of the screen mode.
 */
typedef NS_ENUM(NSUInteger, BCOVPUIScreenMode) {

    /** Default mode **/
    BCOVPUIScreenModeNormal,

    /** Present full screen **/
    BCOVPUIScreenModeFull
};


/**
 * Conform to this protocol to receive information for regarding the BCOVPUIPlayerView.
 */
@protocol BCOVPUIPlayerViewDelegate <NSObject>
@optional

/**
 * Called when the playerView is finished transitioning to a new screen mode.
 *
 * @param playerView The player view that is transitioning.
 * @param screenMode The screen mode that was transitioned to.
 */
- (void)playerView:(BCOVPUIPlayerView *)playerView didTransitionToScreenMode:(BCOVPUIScreenMode)screenMode;

/**
 * Called when the playerView controls faded out.
 *
 * @param playerView The player view that manages the controls.
 * @param controlsFadingView The controls fading view that faded out.
 */
- (void)playerView:(BCOVPUIPlayerView *)playerView controlsFadingViewDidFadeOut:(UIView *)controlsFadingView;

/**
 * Called when the playerView controls faded in.
 *
 * @param playerView The player view that manages the controls.
 * @param controlsFadingView The controls fading view that faded in.
 */
- (void)playerView:(BCOVPUIPlayerView *)playerView controlsFadingViewDidFadeIn:(UIView *)controlsFadingView;

@end


/**
 * Optional configuration for a player view.
 */
@interface BCOVPUIPlayerViewOptions : NSObject

/**
 * This view controller will be used for features that require a presenting view
 * controller, like full screen mode or the closed-caption popover.
 */
@property (nonatomic, weak) UIViewController *presentingViewController;

/**
 * The time in seconds to jump back when the jump back button is pressed.
 * Defaults to 10 seconds.
 */
@property (nonatomic, assign) NSTimeInterval jumpBackInterval;

/**
 * The time in seconds since the last touch before fading the controls.
 * Defaults to 5 seconds.
 */
@property (nonatomic, assign) NSTimeInterval hideControlsInterval;

/**
 * The time in seconds for animating the hiding of the controls.
 * Defaults to .5 seconds.
 */
@property (nonatomic, assign) NSTimeInterval hideControlsAnimationDuration;

/**
 * The time in seconds for animating the showing of the controls.
 * Defaults to .2 seconds.
 */
@property (nonatomic, assign) NSTimeInterval showControlsAnimationDuration;

@end


/**
 * View for displaying video and controls.
 */
@interface BCOVPUIPlayerView : UIView

/**
 * The playback controller associated with this player view.
 */
@property (nonatomic, weak, readonly) id<BCOVPlaybackController> playbackController;

/**
 * A delegate that conforms to BCOVPUIPlayerViewDelegate.
 */
@property (nonatomic, weak) id<BCOVPUIPlayerViewDelegate> delegate;

/**
 * View that holds the video content.
 */
@property (nonatomic, weak, readonly) UIView *contentContainerView;

/**
 * View intended to contain views that overlay the video content.
 */
@property (nonatomic, weak, readonly) UIView *contentOverlayView;

/**
 * View intended to contain control elements that should not be
 * faded out/in.
 */
@property (nonatomic, weak, readonly) UIView *controlsStaticView;

/**
 * View intended to contain control elements that should be
 * faded out/in.
 */
@property (nonatomic, weak, readonly) UIView *controlsFadingView;

/**
 * View intended to contain views that should overlay all other views.
 */
@property (nonatomic, weak, readonly) UIView *overlayView;

/**
 * Content controls view. This view should exist in either the contentOverlayView
 * or controlsFadingView view.
 */
@property (nonatomic, weak, readonly) BCOVPUIBasicControlView *controlsView;

/**
 * Initializes a BCOVPUIPlayerView using default options with the given
 * BCOVPlaybackController.
 *
 * @param playbackController The playback controller used by the player view. This
 * must not be nil.
 *
 * @return Fully initialized player view.
 */
- (instancetype)initWithPlaybackController:(id<BCOVPlaybackController>)playbackController;

/**
 * Initializes a BCOVPUIPlayerView using the provided BCOVPUIPlayerViewOptions 
 * and BCOVPlaybackController.
 *
 * @param playbackController The playback controller used by the player view. This
 * must not be nil.
 * @param options The options for the player view. If nil, default options will be used.
 *
 * @return Fully initialized player view.
 */
- (instancetype)initWithPlaybackController:(id<BCOVPlaybackController>)playbackController options:(BCOVPUIPlayerViewOptions *)options;

/**
 * Initializes a BCOVPUIPlayerView using the provided BCOVPUIPlayerViewOptions, 
 * BCOVPlaybackController and customized BCOVPUIBasicControlView.
 *
 * @param playbackController The playback controller used by the player view. This
 * must not be nil.
 * @param options The options for the playview. If nil, default options will be used.
 * @param controlsView The controls view to use in the player view.  If nil, default
 * controls view will be used.
 *
 * @return Fully initialized player view.
 */
- (instancetype)initWithPlaybackController:(id<BCOVPlaybackController>)playbackController options:(BCOVPUIPlayerViewOptions *)options controlsView:(BCOVPUIBasicControlView *)controlsView NS_DESIGNATED_INITIALIZER;

/**
 * Performs screen transition to the designated mode.
 *
 * @param screenMode The screen mode to transition to.
 */
- (void)performScreenTransitionWithScreenMode:(BCOVPUIScreenMode)screenMode;

@end
