//
// BCOVPUISlider.h
// BrightcovePlayerUI
//
// Copyright (c) 2015 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>


/**
 * A subsclass of UISlider that provides a "buffered" track.
 */
@interface BCOVPUISlider : UISlider

/**
 * The amount of buffer. This value will be pinned to min/max.
 */
@property(nonatomic) float bufferProgress;

/**
 * Set to YES to change the slider's UI to the advertising state.
 */
@property(nonatomic, readwrite) BOOL advertisingMode;

/**
 * The tint color to be used for the buffered area.
 */
@property(nonatomic, copy) UIColor *bufferProgressTintColor;

/**
 * Sets the amount of buffer with a possible animation.
 * This value will be pinned to min/max.
 *
 * @param bufferedProgress The progress to set.
 * @param animated Whether to animate.
 */
- (void)setBufferProgress:(float)bufferedProgress animated:(BOOL)animated;

/**
 * Sets the content track image for the specified state.
 *
 * @param image The image to set.
 * @param state The state to set.
 */
- (void)setContentTrackImage:(UIImage *)image forState:(UIControlState)state;

/**
 * Sets the buffered track image for the specified state.
 *
 * @param image The image to set.
 * @param state The state to set.
 */
- (void)setBufferTrackImage:(UIImage *)image forState:(UIControlState)state;

@end
