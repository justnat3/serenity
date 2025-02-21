/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "MCTSTree.h"
#include <LibChess/Chess.h>
#include <LibChess/UCIEndpoint.h>

class ChessEngine : public Chess::UCI::Endpoint {
    C_OBJECT(ChessEngine)
public:
    virtual ~ChessEngine() override = default;

    virtual void handle_uci() override;
    virtual void handle_position(Chess::UCI::PositionCommand const&) override;
    virtual void handle_go(Chess::UCI::GoCommand const&) override;
    virtual void handle_quit() override;
    virtual void handle_unexpected_eof() override;

    Function<void(int)> on_quit;

private:
    ChessEngine() = default;
    ChessEngine(NonnullRefPtr<Core::IODevice> in, NonnullRefPtr<Core::IODevice> out)
        : Endpoint(in, out)
    {
    }

    Chess::Board m_board;
    Optional<MCTSTree> m_last_tree;
};
